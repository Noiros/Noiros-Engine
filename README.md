# Custom Game Engine

Un moteur de jeu Open Source à but éducatif, conçu en C++ avec **SDL3** et **OpenGL**. Ce projet vise à fournir une base solide pour le développement de jeux 2D et 3D avec une séparation stricte entre l'éditeur et le runtime.

## 🚀 Concept

Ce projet est né de la volonté d'apprendre et de comprendre les mécanismes internes d'un moteur de jeu. Il n'est pas seulement un outil de création, mais aussi un terrain d'expérimentation pour les concepts d'architecture logicielle appliquée au jeu vidéo.

L'objectif principal est de proposer un environnement de développement complet avec :
- Un **Editor** pour concevoir les scènes et gérer les ressources.
- Un **Runtime** léger et performant pour l'exécution finale du jeu.
- Un **Core Engine** partagé qui gère la logique de base.

## 🛠 Technologies

Le moteur s'appuie sur des bibliothèques robustes et modernes :
- **SDL3** : Pour la gestion des fenêtres, des entrées utilisateur et du cycle de vie de l'application.
- **OpenGL** : API de rendu graphique pour la 2D et la 3D.
- **glad** : Chargeur de fonctions OpenGL 4.6 core.
- **GLM (OpenGL Mathematics)** : Pour tous les calculs mathématiques liés à l'espace 2D et 3D.
- **CMake** : Pour une gestion simple et multiplateforme de la compilation.

## 📂 Structure

- `main.cpp` : point d'entrée.
- `engine/` : code du moteur.

Toutes les dépendances (SDL3, glad, GLM) sont récupérées automatiquement par CMake via `FetchContent` — pas de `thirdparty/`, pas de sous-modules.

## ⚙️ Compilation

### Prérequis
- Un compilateur supportant le **C++20**.
- **CMake** 3.24 ou supérieure.
- **Python 3** (utilisé par glad pour générer le loader OpenGL ; CMake installe `jinja2` si besoin).

### Étapes
```powershell
cmake -B build
cmake --build build
```

L'exécutable est produit dans `build/bin/`.

## 📜 Licence

Ce projet est un logiciel Open Source.

---
*Projet à but éducatif développé avec passion.*
