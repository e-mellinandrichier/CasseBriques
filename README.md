<a id="en"></a>

<div align="center">
  <a href="#en">🇬🇧 English</a> · 
  <a href="#fr">🇫🇷 français</a>
</div>

# CasseBriques

A learning project building a brick-breaker game in C++ with [SFML](https://www.sfml-dev.org/). 

The first milestone is all about setting up a lightweight game engine that can render objects on screen, process keyboard and mouse input, and detect simple collisions.

---

## Architecture overview

### Step 1: mini game engine ✅

**core classes:**

- **`GameObject`**: base class for all game objects
  - position, velocity, rotation
  - rendering (circle/rectangle shapes)
  - axis-aligned bounding box (AABB) collision detection
  - virtual `update(dt)` and `render()` methods

- **`Game`**: Main game loop manager
  - SFML window creation and management
  - 60 FPS game loop with delta-time updates
  - collision checking between objects
  - test object initialization

- **`InputManager`** (singleton): keyboard & mouse input
  - event-based key callbacks
  - continuous key state tracking
  - mouse position & button tracking
  - window close detection

- **`CollisionDetector`**: collision utilities
  - AABB-to-AABB collision detection
  - circle-to-AABB collision detection
  - collision normal calculation
  - closest point on AABB calculation

**Utilities:**
- `AABB` struct: Axis-aligned bounding box with helper methods
- `ShapeType` enum: CIRCLE or RECTANGLE
- `Constants.h`: global game constants (window size, FPS, colors, etc.)

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for detailed architecture and [docs/ClassDiagramStep1.puml](docs/ClassDiagramStep1.puml) for class diagrams.

### Step 2: Brick-Breaker gameplay ⏳

**planned additions:**

- **`Paddle`** (extends GameObject): player-controlled paddle
  - Left/right movement
  - Collision response with ball

- **`Ball`** (extends GameObject): game ball
  - launch mechanics
  - physics-based bouncing on collisions
  - reset functionality

- **`Brick`** (extends GameObject): destructible bricks
  - health/durability system
  - point rewards
  - visual destruction feedback

- **`Scene`**: game state manager
  - paddle, ball, and brick management
  - win/lose condition handling
  - level progression

- **`ScoreManager`** (singleton): score tracking
  - current & high score management
  - score persistence (save/load)

See [docs/ClassDiagramStep2.puml](docs/ClassDiagramStep2.puml) for planned architecture.

---

## Prerequisites

- **C++17** or newer
- **SFML 2.5+** (2.6 recommended)
- **CMake 3.16+**
- **Compiler**: GCC, Clang, MSVC, or equivalent

See [BUILD.md](BUILD.md) for platform-specific installation instructions.

---

## Development setup

For cross-platform development with Windows, macOS, and Linux:

1. **install local dependencies** (see [BUILD.md](BUILD.md))
2. **clone and build**:
   ```bash
   git clone <repo>
   cd CasseBriques
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```
3. **or use Docker** for consistent environment across all platforms

### Testing

Run the built executable:
```bash
./build/CasseBriques    # Linux/macOS
build\Release\CasseBriques.exe  # Windows
```

#### Suggested manual tests:
- Confirm that a `GameObject` moves correctly when its velocity changes.
- Verify that rotation affects the intended objects.
- Ensure collisions between two rectangles are detected.
- Bind a keyboard key through the `InputManager` and check that the callback fires.


---

## Roadmap

| step | goal | status |
|------|------|--------|
| 1 | mini game engine (GameObject, InputManager, AABB collisions) | ✅ complete |
| 2 | brick-breaker gameplay (paddle, ball, bricks, scoring) | ⏳ in progress |
| 3 | audio/visual polish, menu, end screen | ⏳ planned |
| 4 | packaging and multi-platform distribution | ⏳ planned |

---

## Documentation

- **[BUILD.md](BUILD.md)** - detailed build instructions for all platforms + Docker
- **[docs/ARCHITECTURE.md](docs/ARCHITECTURE.md)** - complete architecture documentation (EN/FR)
- **[docs/casse-briques.md](docs/casse-briques.md)** - original assignment specification (FR/EN)
- **[docs/ClassDiagramStep1.puml](docs/ClassDiagramStep1.puml)** - step 1 class diagram (PlantUML)
- **[docs/ClassDiagramStep1.png](docs/ClassDiagramStep1.png)** - step 1 class diagram (image)
- **[docs/ClassDiagramStep2.puml](docs/ClassDiagramStep2.puml)** - step 2 planned architecture (PlantUML)
- **[docs/ClassDiagramStep2.png](docs/ClassDiagramStep2.png)** - step 2 planned architecture (image)

---

## Resources

- [SFML official documentation](https://www.sfml-dev.org/documentation/2.6.0/)
- [SFML tutorials](https://www.sfml-dev.org/tutorials/2.6/)
- [Game programming Patterns](https://gameprogrammingpatterns.com/)
- [2D collision detection](https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection)

---

## Contributors

[Emanuelle](https://github.com/e-mellinandrichier), [Leila](https://github.com/leila-wilde) & [
Abdelrahmane](https://github.com/abdelrahmane-amiri)

---

## License


---

<a id="fr"></a>

<div align="center">
  <a href="#en">🇬🇧 English</a> · 
  <a href="#fr">🇫🇷 français</a>
</div>

# CasseBriques

Un projet d'apprentissage pour construire un jeu de casse-briques en C++ avec [SFML](https://www.sfml-dev.org/).

Le premier jalon consiste à mettre en place un moteur de jeu léger qui peut rendre les objets à l'écran, traiter les entrées clavier et souris, et détecter les collisions simples.

---

## Aperçu architecture

### Étape 1: mini moteur de jeu ✅

**classes principales:**

- **`GameObject`**: classe de base pour tous les objets du jeu
  - position, vitesse, rotation
  - rendu (formes cercle/rectangle)
  - détection de collision par boîte englobante alignée aux axes (AABB)
  - méthodes virtuelles `update(dt)` et `render()`

- **`Game`**: gestionnaire de boucle de jeu principale
  - création et gestion de fenêtre SFML
  - boucle de jeu 60 FPS avec mises à jour delta-time
  - vérification de collision entre objets
  - initialisation d'objets de test

- **`InputManager`** (singleton): entrée clavier et souris
  - rappels clé basés sur les événements
  - suivi continu de l'état des touches
  - suivi de la position de la souris et des boutons
  - détection de fermeture de fenêtre

- **`CollisionDetector`**: utilitaires de collision
  - détection de collision AABB-to-AABB
  - détection de collision cercle-to-AABB
  - calcul de normale de collision
  - calcul du point le plus proche sur AABB

**Utilitaires:**
- Structure `AABB`: boîte englobante alignée aux axes avec méthodes d'aide
- Énumération `ShapeType`: CERCLE ou RECTANGLE
- `Constants.h`: constantes globales du jeu (taille fenêtre, FPS, couleurs, etc.)

Voir [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) pour l'architecture détaillée et [docs/ClassDiagramStep1.puml](docs/ClassDiagramStep1.puml) pour les diagrammes de classe.

### Étape 2: gameplay Casse-Briques ⏳

**ajouts prévus:**

- **`Paddle`** (extends GameObject): palette contrôlée par le joueur
  - Mouvement gauche/droite
  - Réponse de collision avec la balle

- **`Ball`** (extends GameObject): balle du jeu
  - mécaniques de lancement
  - rebond physique sur collisions
  - fonctionnalité de réinitialisation

- **`Brick`** (extends GameObject): briques destructibles
  - système de santé/durabilité
  - récompenses de points
  - rétroaction visuelle de destruction

- **`Scene`**: gestionnaire d'état du jeu
  - gestion palette, balle et briques
  - gestion des conditions de victoire/défaite
  - progression de niveau

- **`ScoreManager`** (singleton): suivi des scores
  - gestion du score actuel et du meilleur score
  - persistance des scores (sauvegarde/chargement)

Voir [docs/ClassDiagramStep2.puml](docs/ClassDiagramStep2.puml) pour l'architecture prévue.

---

## Prérequis

- **C++17** ou plus récent
- **SFML 2.5+** (2.6 recommandé)
- **CMake 3.16+**
- **Compilateur**: GCC, Clang, MSVC, ou équivalent

Voir [BUILD.md](BUILD.md) pour les instructions d'installation spécifiques à chaque plateforme.

---

## Configuration du développement

Pour le développement multi-plateforme avec Windows, macOS et Linux:

1. **installez les dépendances locales** (voir [BUILD.md](BUILD.md))
2. **clonez et compilez**:
   ```bash
   git clone <repo>
   cd CasseBriques
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```
3. **ou utilisez Docker** pour un environnement cohérent sur toutes les plateformes

### Tests

Exécutez l'exécutable compilé:
```bash
./build/CasseBriques    # Linux/macOS
build\Release\CasseBriques.exe  # Windows
```

#### Tests manuels suggérés:
- Confirmez qu'un `GameObject` se déplace correctement quand sa vitesse change.
- Vérifiez que la rotation affecte les objets visés.
- Assurez-vous que les collisions entre deux rectangles sont détectées.
- Liez une touche clavier via `InputManager` et vérifiez que le rappel se déclenche.


---

## Feuille de route

| étape | objectif | statut |
|------|----------|--------|
| 1 | mini moteur de jeu (GameObject, InputManager, collisions AABB) | ✅ complète |
| 2 | gameplay casse-briques (palette, balle, briques, score) | ⏳ en cours |
| 3 | polissage audio/visuel, menu, écran de fin | ⏳ planifiée |
| 4 | empaquetage et distribution multi-plateforme | ⏳ planifiée |

---

## Documentation

- **[BUILD.md](BUILD.md)** - instructions de compilation détaillées pour toutes les plateformes + Docker
- **[docs/ARCHITECTURE.md](docs/ARCHITECTURE.md)** - documentation complète d'architecture (EN/FR)
- **[docs/casse-briques.md](docs/casse-briques.md)** - spécification d'assignation originale (FR/EN)
- **[docs/ClassDiagramStep1.puml](docs/ClassDiagramStep1.puml)** - diagramme de classe étape 1 (PlantUML)
- **[docs/ClassDiagramStep1.png](docs/ClassDiagramStep1.png)** - diagramme de classe étape 1 (image)
- **[docs/ClassDiagramStep2.puml](docs/ClassDiagramStep2.puml)** - architecture prévue étape 2 (PlantUML)
- **[docs/ClassDiagramStep2.png](docs/ClassDiagramStep2.png)** - architecture prévue étape 2 (image)

---

## Ressources

- [Documentation officielle SFML](https://www.sfml-dev.org/documentation/2.6.0/)
- [Tutoriels SFML](https://www.sfml-dev.org/tutorials/2.6/)
- [Motifs de Programmation de Jeu](https://gameprogrammingpatterns.com/)
- [Détection de Collision 2D](https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection)

---

## Contributeurs

[Emanuelle](https://github.com/e-mellinandrichier), [Leila](https://github.com/leila-wilde) & [Abdelrahmane](https://github.com/abdelrahmane-amiri)

---

## Licence

