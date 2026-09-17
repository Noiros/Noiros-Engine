cmake_minimum_required(VERSION 3.24)
project(NoirosEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)

# glad generates the GL loader with Python at configure time; jinja2 is its only extra need.
find_package(Python REQUIRED COMPONENTS Interpreter)
execute_process(COMMAND ${Python_EXECUTABLE} -c "import jinja2" RESULT_VARIABLE HAVE_JINJA2
        OUTPUT_QUIET ERROR_QUIET)
if(NOT HAVE_JINJA2 EQUAL 0)
    message(STATUS "Installing jinja2 for glad")
    execute_process(COMMAND ${Python_EXECUTABLE} -m pip install --user jinja2
            COMMAND_ERROR_IS_FATAL ANY)
endif()

FetchContent_Declare(glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.3 GIT_SHALLOW TRUE)

FetchContent_Declare(SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.16 GIT_SHALLOW TRUE)

FetchContent_Declare(glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v2.0.8 GIT_SHALLOW TRUE
        SOURCE_SUBDIR cmake)

FetchContent_MakeAvailable(glm SDL3 glad)

glad_add_library(glad_gl_core_46 STATIC API gl:core=4.6)

add_executable(Noiros main.cpp core/Engine.cpp
        core/Window.cpp
        core/Window.h)
target_include_directories(Noiros PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Noiros PRIVATE SDL3::SDL3 glad_gl_core_46 glm::glm)

# SDL3 is a shared lib: keep it next to the executable
add_custom_command(TARGET Noiros POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3> $<TARGET_FILE_DIR:Noiros>)
