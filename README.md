# CasseBriques

## 1. Overview

`CasseBriques` is a learning project that walks through building a brick-breaker game in C++ with [SFML](https://www.sfml-dev.org/). The first milestone is all about setting up a lightweight game engine that can render objects on screen, process keyboard and mouse input, and detect simple collisions.

## 2. Goals for Step 1

- Provide a generic management layer for `GameObject` instances.
- Render simple shapes (`sf::CircleShape`, `sf::RectangleShape`) with configurable position and size.
- Enable translation based on a velocity vector and delta time.
- Optionally rotate objects.
- Attach an axis-aligned bounding box (AABB) to each object.
- Detect collisions between `GameObject` instances.
- Implement an `InputManager` that listens to SFML events (keyboard, mouse) and triggers callbacks.

## 3. Suggested Architecture

- `GameObject` (base class)  
  - Position, velocity, rotation.  
  - Holds a reference to an SFML shape for rendering.  
  - Virtual methods `update(float dt)` and `draw(sf::RenderWindow&)`.  
  - Helper methods for computing the AABB (`getBounds()`).

- `GameObjectManager`  
  - Stores and updates all `GameObject` instances.  
  - Drives the `update/draw` loop and collision checks.

- `InputManager`  
  - Maps `Action -> Callback`.  
  - `handleEvent(const sf::Event&)` relays events from the main loop.  
  - `isPressed(sf::Keyboard::Key)` exposes continuous input states.

- `Collision` (namespace or utility class)  
  - Functions for testing intersections between two AABBs.

- `Game`  
  - Hosts the SFML main loop (window creation, timing, event dispatch).  
  - Instantiates `GameObjectManager` and `InputManager`.  
  - Will later expose the scene (paddle, ball, bricks).

## 4. Prerequisites

- C++17 or newer.
- SFML 2.6 (or 2.5.x) installed locally.
- CMake ≥ 3.16 recommended for cross-platform builds.

### Installing SFML (macOS)

```bash
brew install sfml
```

### Installing SFML (Windows)

- Install SFML from the official website or via `vcpkg`.
- Configure the environment/linker settings in CMake or Visual Studio.

## 5. Building (CMake example)

```bash
mkdir build
cd build
cmake .. -DSFML_DIR=/usr/local/Cellar/sfml/2.6.0/lib/cmake/SFML
cmake --build .
```

> Adjust `SFML_DIR` to match your setup. On Windows, consider using `vcpkg` and `-DCMAKE_TOOLCHAIN_FILE`.

## 6. Roadmap

- ✅ Step 1: Mini game engine (GameObject, InputManager, AABB collisions).
- ⏳ Step 2: Brick-breaker gameplay (paddle, ball, bricks, scoring).
- ⏳ Step 3: Audio/visual polish, menu, end screen.
- ⏳ Step 4: Packaging and multi-platform distribution.

## 7. Suggested Manual Tests

- Confirm that a `GameObject` moves correctly when its velocity changes.  
- Verify that rotation affects the intended objects.  
- Ensure collisions between two rectangles are detected.  
- Bind a keyboard key through the `InputManager` and check that the callback fires.

## 8. Useful Resources

- [SFML documentation](https://www.sfml-dev.org/documentation/2.6.0/)
- [SFML tutorials](https://www.sfml-dev.org/tutorials/2.6/)
- [Design Patterns for Games](https://gameprogrammingpatterns.com/)
- [AABB collision math](https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection)