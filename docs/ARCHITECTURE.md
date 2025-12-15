<a id="fr"></a>

<div align="center">
  <a href="#en">🇬🇧 English</a> · 
  <a href="#fr">🇫🇷 français</a>
</div>

# Architecture 

# Étape 1 : mini moteur de jeu

## Aperçu

L'étape 1 consiste à construire un **mini moteur de jeu** qui gère :
- la gestion des objets du jeu (positionnement, mouvement, rendu)
- la détection des collisions entre les objets
- le traitement de l'entrée utilisateur (clavier et souris)
- l'exécution de la boucle de jeu principale à 60 FPS

Ce moteur sera étendu à l'étape 2 pour créer un jeu de casse-briques jouable.

---

## Diagramme de classes (étape 1)

```
┌─────────────────────────────────────────────────────────────┐
│                      Game (boucle principale)               │
│  ┌─ créer la fenêtre SFML                                   │
│  ┌─ mettre à jour tous les GameObjects                      │
│  ┌─ rendre tous les GameObjects                             │
│  └─ interroger InputManager pour les événements             │
└─────────────────────────────────────────────────────────────┘
           │
           ├─→ InputManager (singleton)
           │   ┌─ suivre l'état du clavier
           │   ├─ suivre l'état de la souris
           │   └─ exécuter les rappels
           │
           ├─→ GameObject (classe de base)
           │   ┌─ position (x, y)
           │   ├─ vitesse (vx, vy)
           │   ├─ angle de rotation
           │   ├─ taille (largeur, hauteur)
           │   ├─ boîte de collision AABB
           │   ├─ update(dt)
           │   ├─ render()
           │   └─ getCollisionBox()
           │
           └─→ CollisionDetector (utilitaire)
               ┌─ checkAABB()
               ├─ checkCircleAABB()
               └─ getCollisionNormal()
```
---

## Classes principales

### 1. GameObject

**Objectif :** classe de base pour tous les objets du jeu.

**Responsabilités :**
- stocker la position, la vitesse, la taille, la rotation, la couleur
- maintenir une boîte englobante alignée sur les axes (AABB) pour les collisions
- mettre à jour la position à chaque frame en fonction de la vitesse et du delta-temps
- se rendre lui-même avec SFML
- supporter les formes circulaires et rectangulaires

**Méthodes clés :**
```cpp
void update(float deltaTime);           // Déplacer l'objet
void render(sf::RenderWindow& window);  // Dessiner l'objet
AABB getCollisionBox() const;           // Retourner la boîte de collision
void setVelocity(float vx, float vy);   // Définir la vitesse
void setPosition(float x, float y);     // Définir la position
void rotate(float angleDegrees);        // Définir la rotation
```

**Propriétés clés :**
```cpp
sf::Vector2f position;      // Centre de l'objet (x, y)
sf::Vector2f velocity;      // Vecteur de vitesse (vx, vy)
float rotation;             // Rotation en degrés
sf::Vector2f size;          // Largeur et hauteur
sf::Color color;            // Couleur d'affichage
ShapeType shapeType;        // CIRCLE ou RECTANGLE
AABB collisionBox;          // Boîte englobante pour la détection de collision
```

**Support des formes :**
- **Cercle :** utilise `sf::CircleShape` pour le rendu
- **Rectangle :** utilise `sf::RectangleShape` pour le rendu
- AABB est calculé comme une boîte englobante autour des deux formes

---

### 2. InputManager (singleton)

**Objectif :** gestion centralisée de l'entrée clavier et souris.

**Responsabilités :**
- sonder les événements SFML de la fenêtre du jeu
- suivre quelles touches sont actuellement enfoncées/maintenues
- suivre la position et l'état des boutons de la souris
- exécuter les fonctions de rappel enregistrées lorsque les événements se produisent
- fournir une interface de requête simple pour l'état de l'entrée

**Méthodes clés :**
```cpp
static InputManager& getInstance();     // Accesseur singleton
void update(const sf::RenderWindow& w); // Sonder les événements chaque frame
void registerKeyCallback(sf::Keyboard::Key key, std::function<void()> callback);
void registerMouseCallback(sf::Mouse::Button button, std::function<void()> callback);
bool isKeyPressed(sf::Keyboard::Key key) const;
bool isMouseButtonPressed(sf::Mouse::Button button) const;
sf::Vector2f getMousePosition() const;
```

**Propriétés clés :**
```cpp
std::map<sf::Keyboard::Key, bool> keyPressed;           // État actuel de la touche
std::map<sf::Keyboard::Key, std::vector<Callback>> keyCallbacks;
sf::Vector2f mousePosition;
std::map<sf::Mouse::Button, std::vector<Callback>> mouseCallbacks;
```

**Mécanisme de rappel :**
- Les fonctions enregistrées avec `registerKeyCallback()` s'exécutent immédiatement lorsqu'un événement clé se produit
- Permet de découpler la logique d'entrée de la logique du jeu
- Plusieurs rappels peuvent être enregistrés pour la même touche

**Exemple d'utilisation (dans Game::init()) :**
```cpp
InputManager& input = InputManager::getInstance();
input.registerKeyCallback(sf::Keyboard::Left, [this]() { 
    moveLeft(); 
});
input.registerMouseCallback(sf::Mouse::Left, [this]() { 
    onClick(); 
});
```

---

### 3. CollisionDetector (classe utilitaire)

**Objectif :** détecter les collisions entre les objets du jeu.

**Responsabilités :**
- Effectuer les tests de collision des boîtes englobantes alignées sur les axes (AABB)
- Effectuer les tests de collision cercle-vers-AABB
- Calculer la normale de collision (direction d'impact)
- Fournir des fonctions d'aide statiques (pas d'état nécessaire)

**Méthodes clés :**
```cpp
// Collision AABB-vers-AABB
static bool checkAABB(const AABB& box1, const AABB& box2);

// Collision cercle-vers-AABB
static bool checkCircleAABB(const sf::Vector2f& circleCenter, 
                            float radius, 
                            const AABB& box);

// Calculer la normale de collision pour le rebond
static sf::Vector2f getCollisionNormal(const AABB& box1, 
                                       const AABB& box2);
```

**Structures clés :**
```cpp
struct AABB {
    float x, y;           // Coin supérieur gauche
    float width, height;  // Dimensions
    
    // Méthodes d'aide
    float left() const;
    float right() const;
    float top() const;
    float bottom() const;
};
```

**Aperçu de l'algorithme :**
- **Collision AABB :** Deux boîtes se chevauchent si :
  - `box1.right > box2.left && box1.left < box2.right` (chevauchement en X)
  - `box1.bottom > box2.top && box1.top < box2.bottom` (chevauchement en Y)
  
- **Collision cercle-AABB :** le cercle se chevauche si le point le plus proche de la boîte est à portée
  - trouver le point le plus proche de la boîte au centre du cercle
  - retourner vrai si la distance ≤ rayon

- **Normale de collision :** direction perpendiculaire à la surface de contact
  - utilisée à l'étape 2 pour la physique de rebond

---

### 4. Game (boucle principale)

**Objectif :** orchestrer le moteur de jeu global et la boucle.

**Responsabilités :**
- créer et gérer la fenêtre de rendu SFML
- maintenir une liste des objets de jeu actifs
- appeler update et render sur tous les objets à chaque frame
- gérer le timing des frames (cible 60 FPS)
- gérer les événements de la fenêtre (fermeture, redimensionnement)
- intégrer InputManager, GameObjects et CollisionDetector

**Méthodes clés :**
```cpp
void init();                              // Initialiser la fenêtre du jeu et les objets
void run();                               // Boucle de jeu principale
void update(float deltaTime);             // Mettre à jour tous les objets
void render();                            // Rendre tous les objets
void addGameObject(GameObject* obj);      // Ajouter un objet à la scène
void removeGameObject(GameObject* obj);   // Supprimer un objet de la scène
```

**Propriétés clés :**
```cpp
sf::RenderWindow window;
std::vector<GameObject*> gameObjects;
float targetFPS = 60.0f;
float deltaTime = 0.0f;
bool isRunning = true;
```

**Pseudo-code de la boucle principale :**
```
while la fenêtre est ouverte:
    dt = temps depuis la dernière frame
    
    InputManager.update(fenêtre)         // Sonder clavier/souris
    
    for chaque GameObject:
        obj.update(dt)                   // Mettre à jour la position
        
    détection des collisions (débogage optionnel)
    
    window.clear()
    for chaque GameObject:
        obj.render(window)               // Dessiner à la fenêtre
    window.display()
    
    pause pour maintenir 60 FPS
```

---

## Flux de données

```
1. PHASE D'ENTRÉE
   l'utilisateur appuie sur une touche
   │
   └─→ SFML détecte l'événement
       └─→ InputManager.update() traite l'événement
           └─→ les rappels enregistrés s'exécutent
               └─→ l'état du jeu change (par exemple, "se déplacer à gauche")

2. PHASE DE MISE À JOUR
   for chaque GameObject:
       │
       └─→ GameObject.update(dt)
           ├─→ appliquer la vitesse : newPos = oldPos + velocity * dt
           ├─→ mettre à jour AABB en fonction de la nouvelle position
           └─→ (futur : gérer les rebonds en fonction des collisions)

3. PHASE DE COLLISION (optionnel, pour le débogage)
   for chaque paire de GameObjects:
       │
       └─→ CollisionDetector.checkAABB()
           └─→ enregistrer/visualiser les collisions

4. PHASE DE RENDU
   window.clear()
   for chaque GameObject:
       │
       └─→ GameObject.render(window)
           └─→ dessiner la forme à la position/rotation actuelle
   window.display()

5. RÉPÉTER à ~60 FPS
```

---

## Structure des fichiers du repo

```
CasseBriques/
├── Dockerfile                  # définition de l'image Docker
├── docker-compose.yml          # configuration Docker Compose
├── CMakeLists.txt              # configuration de la compilation CMake
├── Makefile                    # wrapper de compilation pratique
├── .gitignore                  # règles d'ignorance Git
├── README.md                   # instructions de configuration et d'utilisation
│
├── src/
│   ├── main.cpp                # point d'entrée, crée Game
│   ├── Game.h / Game.cpp       # boucle principale, gestion de la fenêtre
│   ├── GameObject.h / GameObject.cpp     # classe d'objet de base
│   ├── InputManager.h / InputManager.cpp # gestion de l'entrée
│   └── CollisionDetector.h / CollisionDetector.cpp  # Tests de collision
│
├── include/
│   ├── Types.h                # types partagés (AABB, ShapeType, etc.)
│   └── Constants.h            # constantes du jeu (taille de fenêtre, FPS, etc.)
│
├── assets/                    # (espace réservé pour plus tard)
│   └── .gitkeep
│
└── docs/
    └── ARCHITECTURE.md        # ce fichier !
```

---

## Décisions de conception clés

### 1. Classe de base GameObject vs composition

**Décision :** utiliser l'héritage (classe de base GameObject) pour l'instant.

**Justification :**
- simple et familier pour les débutants en C++
- facile à étendre (Paddle, Ball, Brick à l'étape 2)
- évite la sur-ingénierie à ce stade
- peut être refactorisé en ECS ultérieurement si nécessaire

---

### 2. Singleton pour InputManager

**Décision :** utiliser le modèle singleton pour InputManager.

**Justification :**
- un seul système d'entrée nécessaire
- accès facile de n'importe où (`InputManager::getInstance()`)
- évite de passer la référence d'entrée autour
- peut être injecté dans le constructeur pour les tests ultérieurs

---

### 3. Méthodes statiques pour CollisionDetector

**Décision :** toutes les fonctions de collision sont statiques.

**Justification :**
- pas d'état nécessaire
- fonctions d'utilité pure
- facile à tester unitairement
- peut être placé n'importe où (espace de noms séparé)

---

### 4. Collision AABB uniquement (pour l'instant)

**Décision :** l'étape 1 utilise exclusivement AABB (boîtes englobantes alignées sur les axes).

**Justification :**
- simple et rapide pour les objets de base
- cercle-AABB disponible pour le futur (balle vs palette)
- pas de collision consciente de la rotation (mathématiques plus simples)
- peut être mise à niveau vers SAT ultérieurement si nécessaire

---

### 5. Mouvement basé sur le delta-temps

**Décision :** tous les mouvements utilisent le delta-temps (pas de base d'image).

**Justification :**
- physique indépendante du taux de rafraîchissement
- animation fluide à n'importe quel FPS
- facile à mettre à l'échelle (ralenti, avance rapide)

---

## Prochaines étapes (étape 2)

L'étape 2 étendra ce moteur avec :
- **Classe Paddle :** rectangle limité, contrôlé au clavier
- **Classe Ball :** cercle avec vitesse, rebondit sur les objets
- **Classe Brick :** rectangles destructibles avec santé
- **Classe BrickGrid :** gère la mise en page et les collisions du niveau
- Améliorations de la physique (angles de rebond, vitesse)

Les classes du moteur de base ne doivent **pas** changer de manière significative.

---

## Stratégie de test (Étape 1)

### Liste de contrôle des tests manuels
- [ ] La fenêtre s'ouvre et se ferme correctement
- [ ] Au moins 2 GameObjects visibles à l'écran
- [ ] Les objets se déplacent lorsque les touches fléchées sont enfoncées
- [ ] Les objets tournent si applicable
- [ ] La sortie de console de la détection de collision est correcte
- [ ] Aucune fuite mémoire (valgrind)
- [ ] Compile sans avertissements

### Visualisation de débogage
- Dessiner les boîtes de collision AABB dans une couleur différente
- Enregistrer les résultats de la détection de collision dans la console
- Afficher le compteur FPS à l'écran

---

## Guide de style de code

- **Nommage :** `camelCase` pour les variables/méthodes, `PascalCase` pour les classes
- **Commentaires :** pour la logique non évidente
- **En-têtes :** inclure les gardes (pas `#pragma once` pour la portabilité)
- **Pointeurs intelligents :** utiliser `std::unique_ptr` pour les objets possédés (Étape 1+)
- **Constantes :** `const` par défaut, `constexpr` pour les constantes de temps de compilation

---

## Dépendances

- **SFML 2.6 :** Pour les graphiques, la fenêtre, l'entrée
- **CMake 3.16+ :** Pour les compilations multi-plateforme
- **C++17 :** Fonctionnalités C++ modernes (std::optional, std::function, etc.)
- **STL uniquement :** Aucune bibliothèque externe nécessaire pour l'étape 1

---

## Conclusion

Cette architecture fournit une **fondation minimale et propre** pour un moteur de jeu. Elle sépare les préoccupations (entrée, physique, rendu) et facilite l'ajout de fonctionnalités spécifiques au jeu à l'étape 2 sans refactorisation majeure.

---

<a id="en"></a>

<div align="center">
  <a href="#en">🇬🇧 English</a> · 
  <a href="#fr">🇫🇷 français</a>
</div>

# Architecture 

# Step 1: mini game engine

## Overview

Step 1 is to build a **mini game engine** that handles:
- managing game objects (positioning, movement, rendering)
- detecting collisions between objects
- processing user input (keyboard and mouse)
- running the main game loop at 60 FPS

This engine will later be extended in Step 2 to create a playable brick breaker game.

---

## Class diagram (step 1)

```
┌─────────────────────────────────────────────────────────────┐
│                      Game (main loop)                       │
│  ┌─ create SFML window                                      │
│  ┌─ update all GameObjects                                  │
│  ┌─ render all GameObjects                                  │
│  └─ poll InputManager for events                            │
└─────────────────────────────────────────────────────────────┘
           │
           ├─→ InputManager (singleton)
           │   ┌─ track keyboard state
           │   ├─ track mouse state
           │   └─ execute callbacks
           │
           ├─→ GameObject (base class)
           │   ┌─ position (x, y)
           │   ├─ velocity (vx, vy)
           │   ├─ rotation angle
           │   ├─ size (width, height)
           │   ├─ AABB collision box
           │   ├─ update(dt)
           │   ├─ render()
           │   └─ getCollisionBox()
           │
           └─→ CollisionDetector (utility)
               ┌─ checkAABB()
               ├─ checkCircleAABB()
               └─ getCollisionNormal()
```
---

## Core classes

### 1. GameObject

**Purpose:** base class for all objects in the game.

**Responsibilities:**
- store position, velocity, size, rotation, color
- maintain an axis-aligned bounding box (AABB) for collision
- update position each frame based on velocity and delta time
- render itself using SFML
- support both circle and rectangle shapes

**Key methods:**
```cpp
void update(float deltaTime);           // Move object
void render(sf::RenderWindow& window);  // Draw object
AABB getCollisionBox() const;           // Return collision box
void setVelocity(float vx, float vy);   // Set velocity
void setPosition(float x, float y);     // Set position
void rotate(float angleDegrees);        // Set rotation
```

**Key properties:**
```cpp
sf::Vector2f position;      // Center of object (x, y)
sf::Vector2f velocity;      // Velocity vector (vx, vy)
float rotation;             // Rotation in degrees
sf::Vector2f size;          // Width and height
sf::Color color;            // Display color
ShapeType shapeType;        // CIRCLE or RECTANGLE
AABB collisionBox;          // Bounding box for collision detection
```

**Shape support:**
- **Circle:** uses `sf::CircleShape` for rendering
- **Rectangle:** uses `sf::RectangleShape` for rendering
- AABB is calculated as a bounding box around both shapes

---

### 2. InputManager (singleton)

**Purpose:** centralized keyboard and mouse input handling.

**Responsibilities:**
- poll SFML events from the game window
- track which keys are currently pressed/held
- track mouse position and button state
- execute registered callback functions when events occur
- provide simple query interface for input state

**Key methods:**
```cpp
static InputManager& getInstance();     // Singleton accessor
void update(const sf::RenderWindow& w); // Poll events each frame
void registerKeyCallback(sf::Keyboard::Key key, std::function<void()> callback);
void registerMouseCallback(sf::Mouse::Button button, std::function<void()> callback);
bool isKeyPressed(sf::Keyboard::Key key) const;
bool isMouseButtonPressed(sf::Mouse::Button button) const;
sf::Vector2f getMousePosition() const;
```

**Key properties:**
```cpp
std::map<sf::Keyboard::Key, bool> keyPressed;           // Current key state
std::map<sf::Keyboard::Key, std::vector<Callback>> keyCallbacks;
sf::Vector2f mousePosition;
std::map<sf::Mouse::Button, std::vector<Callback>> mouseCallbacks;
```

**Callback mechanism:**
- functions registered with `registerKeyCallback()` execute immediately when key event occurs
- allows decoupling input logic from game logic
- multiple callbacks can be registered for the same key

**Example usage (in Game::init()):**
```cpp
InputManager& input = InputManager::getInstance();
input.registerKeyCallback(sf::Keyboard::Left, [this]() { 
    moveLeft(); 
});
input.registerMouseCallback(sf::Mouse::Left, [this]() { 
    onClick(); 
});
```

---

### 3. CollisionDetector (utility class)

**Purpose:** detect collisions between game objects.

**Responsibilities:**
- perform axis-aligned bounding box (AABB) collision tests
- perform circle-to-AABB collision tests
- calculate collision normal (direction of impact)
- provide static helper functions (no state needed)

**Key methods:**
```cpp
// AABB-to-AABB collision
static bool checkAABB(const AABB& box1, const AABB& box2);

// Circle-to-AABB collision
static bool checkCircleAABB(const sf::Vector2f& circleCenter, 
                            float radius, 
                            const AABB& box);

// Calculate collision normal for bouncing
static sf::Vector2f getCollisionNormal(const AABB& box1, 
                                       const AABB& box2);
```

**Key structures:**
```cpp
struct AABB {
    float x, y;           // Top-left corner
    float width, height;  // Dimensions
    
    // Helper methods
    float left() const;
    float right() const;
    float top() const;
    float bottom() const;
};
```

**Algorithm overview:**
- **AABB collision:** Two boxes overlap if:
  - `box1.right > box2.left && box1.left < box2.right` (X overlap)
  - `box1.bottom > box2.top && box1.top < box2.bottom` (Y overlap)
  
- **Circle-AABB collision:** circle overlaps if closest point on box is within radius
  - find closest point on box to circle center
  - return true if distance ≤ radius

- **Collision normal:** direction perpendicular to surface of contact
  - used in Step 2 for bounce physics

---

### 4. Game (main loop)

**Purpose:** orchestrate the overall game engine and loop.

**Responsibilities:**
- create and manage the SFML render window
- maintain a list of active game objects
- call update and render on all objects each frame
- manage frame timing (target 60 FPS)
- handle window events (close, resize)
- integrate InputManager, GameObjects, and CollisionDetector

**Key methods:**
```cpp
void init();                              // Initialize game window and objects
void run();                               // Main game loop
void update(float deltaTime);             // Update all objects
void render();                            // Render all objects
void addGameObject(GameObject* obj);      // Add object to scene
void removeGameObject(GameObject* obj);   // Remove object from scene
```

**Key properties:**
```cpp
sf::RenderWindow window;
std::vector<GameObject*> gameObjects;
float targetFPS = 60.0f;
float deltaTime = 0.0f;
bool isRunning = true;
```

**Main loop pseudocode:**
```
while window is open:
    dt = time since last frame
    
    InputManager.update(window)         // Poll keyboard/mouse
    
    for each GameObject:
        obj.update(dt)                  // Update position
        
    collision detection (optional debug)
    
    window.clear()
    for each GameObject:
        obj.render(window)              // Draw to window
    window.display()
    
    sleep to maintain 60 FPS
```

---

## Data flow

```
1. INPUT PHASE
   user presses key
   │
   └─→ SFML detects event
       └─→ InputManager.update() processes event
           └─→ registered callbacks execute
               └─→ game state changes (e.g., "move left")

2. UPDATE PHASE
   for each GameObject:
       │
       └─→ GameObject.update(dt)
           ├─→ apply velocity: newPos = oldPos + velocity * dt
           ├─→ update AABB based on new position
           └─→ (future: handle bouncing based on collisions)

3. COLLISION PHASE (optional, for debugging)
   for each pair of GameObjects:
       │
       └─→ collisionDetector.checkAABB()
           └─→ log/visualize collisions

4. RENDER PHASE
   window.clear()
   for each GameObject:
       │
       └─→ GameObject.render(window)
           └─→ draw shape at current position/rotation
   window.display()

5. REPEAT at ~60 FPS
```

---

## Repo file structure

```
CasseBriques/
├── Dockerfile                  # Docker image definition
├── docker-compose.yml          # Docker Compose configuration
├── CMakeLists.txt              # CMake build configuration
├── Makefile                    # convenience build wrapper
├── .gitignore                  # git ignore rules
├── README.md                   # setup and usage instructions
│
├── src/
│   ├── main.cpp               # entry point, creates Game
│   ├── Game.h / Game.cpp       # main loop, window management
│   ├── GameObject.h / GameObject.cpp     # base object class
│   ├── InputManager.h / InputManager.cpp # input handling
│   └── CollisionDetector.h / CollisionDetector.cpp  # Collision tests
│
├── include/
│   ├── Types.h                # shared types (AABB, ShapeType, etc.)
│   └── Constants.h            # game constants (window size, FPS, etc.)
│
├── assets/                    # (placeholder for later)
│   └── .gitkeep
│
└── docs/
    └── ARCHITECTURE.md        # this file!
```

---

## Key design decisions

### 1. GameObject base class vs composition

**Decision:** use inheritance (GameObject base class) for now.

**Rationale:**
- simple and familiar for C++ beginners
- easy to extend (Paddle, Ball, Brick in Step 2)
- avoids over-engineering at this stage
- can refactor to ECS later if needed

---

### 2. Singleton for InputManager

**Decision:** use singleton pattern for InputManager.

**Rationale:**
- only one input system needed
- easy to access from anywhere (`InputManager::getInstance()`)
- avoids passing input reference around
- can be injected in constructor for testing later

---

### 3. Static methods for CollisionDetector

**Decision:** all collision functions are static.

**Rationale:**
- no state needed
- pure utility functions
- easy to unit test
- can be placed anywhere (separate namespace)

---

### 4. AABB-only collision (for now)

**Decision:** step 1 uses AABB (axis-aligned bounding boxes) exclusively.

**Rationale:**
- simple and fast for basic objects
- circle-AABB available for future (ball vs paddle)
- no rotation-aware collision (simpler math)
- can upgrade to SAT later if needed

---

### 5. delta-time based movement

**Decision:** all movement uses delta time (not frame-based).

**Rationale:**
- frame-rate independent physics
- smooth animation at any FPS
- easy to scale (slow-motion, fast-forward)

---

## Next steps (step 2)

Step 2 will extend this engine with:
- **Paddle class:** constrained rectangle, keyboard controlled
- **Ball class:** circle with velocity, bounces off objects
- **Brick class:** destructible rectangles with health
- **BrickGrid class:** manages level layout and collisions
- Physics improvements (bounce angles, speed)

The core engine classes should **not** change significantly.

---

## Testing strategy (Step 1)

### Manual testing checklist
- [ ] Window opens and closes properly
- [ ] At least 2 GameObjects visible on screen
- [ ] Objects move when arrow keys pressed
- [ ] Objects rotate when applicable
- [ ] Collision detection console output is correct
- [ ] No memory leaks (valgrind)
- [ ] Compiles without warnings

### Debug visualization
- Draw AABB collision boxes in different color
- Log collision detection results to console
- Display FPS counter on screen

---

## Code style guide

- **Naming:** `camelCase` for variables/methods, `PascalCase` for classes
- **Comments:** for non-obvious logic
- **Headers:** include guards (not `#pragma once` for portability)
- **Smart Pointers:** use `std::unique_ptr` for owned objects (Step 1+)
- **Constants:** `const` by default, `constexpr` for compile-time constants

---

## Dependencies

- **SFML 2.6:** For graphics, window, input
- **CMake 3.16+:** For cross-platform builds
- **C++17:** Modern C++ features (std::optional, std::function, etc.)
- **STL only:** No external libraries needed for Step 1

---

## Conclusion

This architecture provides a **minimal, clean foundation** for a game engine. It separates concerns (input, physics, rendering) and makes it easy to add game-specific features in Step 2 without major refactoring.
