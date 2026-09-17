#pragma once
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <functional>
#include <typeindex>
#include <any>
#include <mutex>
#include <atomic>

class Event {
public:
    Event() = default;

    class Connection {
    public:
        Connection() = default;
        Connection(Event* bus, std::type_index type, size_t id)
            : bus_(bus), type_(type), id_(id) {}
        Connection(const Connection&) = delete;
        Connection& operator=(const Connection&) = delete;
        Connection(Connection&& other) noexcept { MoveFrom(other); }
        Connection& operator=(Connection&& other) noexcept {
            if (this != &other) { Disconnect(); MoveFrom(other); }
            return *this;
        }
        ~Connection() { Disconnect(); }
        void Disconnect();
        explicit operator bool() const { return bus_ != nullptr; }
    private:
        void MoveFrom(Connection& o) {
            bus_ = o.bus_; type_ = o.type_; id_ = o.id_; o.bus_ = nullptr; o.id_ = 0; o.type_ = std::type_index(typeid(void));
        }
        Event* bus_ = nullptr;
        std::type_index type_ = std::type_index(typeid(void));
        size_t id_ = 0;
    };

    static void SetInstance(Event* instance) { s_instance = instance; }
    static Event& Get() { return *s_instance; }
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;

    template<typename E>
    using Handler = std::function<void(const E&)>;

    template<typename E>
    Connection Subscribe(Handler<E> handler) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto& vec = listeners_[std::type_index(typeid(E))];
        size_t id = ++counter_;
        vec.emplace_back(Listener{ id, [h = std::move(handler)](const std::any& a){ h(std::any_cast<const E&>(a)); } });
        return Connection(this, std::type_index(typeid(E)), id);
    }

    template<typename E>
    void Publish(const E& e) {
        std::vector<Listener> copy;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = listeners_.find(std::type_index(typeid(E)));
            if (it == listeners_.end()) return;
            copy = it->second;
        }
        std::any payload = e;
        for (auto& l : copy) l.fn(payload);
    }

    template<typename E>
    void Post(E e) {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        queue_.push_back(Queued{ std::type_index(typeid(E)), std::move(e) });
    }

    void Pump() {
        std::vector<Queued> local;
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            local.swap(queue_);
        }
        for (auto& q : local) {
            DispatchAny(q.type, q.payload);
        }
    }

    void Unsubscribe(std::type_index type, size_t id) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = listeners_.find(type);
        if (it == listeners_.end()) return;
        auto& vec = it->second;
        vec.erase(std::remove_if(vec.begin(), vec.end(), [id](const Listener& L){ return L.id == id; }), vec.end());
    }

private:
    static Event* s_instance;

    struct Listener {
        size_t id;
        std::function<void(const std::any&)> fn;
    };

    struct Queued {
        std::type_index type;
        std::any payload;
    };

    void DispatchAny(std::type_index type, const std::any& a) {
        std::vector<Listener> copy;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = listeners_.find(type);
            if (it == listeners_.end()) return;
            copy = it->second;
        }
        for (auto& l : copy) l.fn(a);
    }

    std::unordered_map<std::type_index, std::vector<Listener>> listeners_;
    std::mutex mutex_;
    std::atomic_size_t counter_{0};

    std::vector<Queued> queue_;
    std::mutex queue_mutex_;
};

inline void Event::Connection::Disconnect() {
    if (bus_) {
        bus_->Unsubscribe(type_, id_);
        bus_ = nullptr;
    }
}