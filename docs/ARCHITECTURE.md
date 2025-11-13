<a id="fr"></a>

<div align="center">
  <a href="#en">🇬🇧 English</a> · 
  <a href="#fr">🇫🇷 français</a>
</div>

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

**Purpose:** Base class for all objects in the game.

**Responsibilities:**
- Store position, velocity, size, rotation, color
- Maintain an axis-aligned bounding box (AABB) for collision
- Update position each frame based on velocity and delta time
- Render itself using SFML
- Support both circle and rectangle shapes

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

**Shape Support:**
- **Circle:** uses `sf::CircleShape` for rendering
- **Rectangle:** uses `sf::RectangleShape` for rendering
- AABB is calculated as a bounding box around both shapes

---

### 2. InputManager (singleton)

**Purpose:** Centralized keyboard and mouse input handling.

**Responsibilities:**
- Poll SFML events from the game window
- Track which keys are currently pressed/held
- Track mouse position and button state
- Execute registered callback functions when events occur
- Provide simple query interface for input state

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
- Functions registered with `registerKeyCallback()` execute immediately when key event occurs
- Allows decoupling input logic from game logic
- Multiple callbacks can be registered for the same key

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
- Perform axis-aligned bounding box (AABB) collision tests
- Perform circle-to-AABB collision tests
- Calculate collision normal (direction of impact)
- Provide static helper functions (no state needed)

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
   User presses key
   │
   └─→ SFML detects event
       └─→ InputManager.update() processes event
           └─→ Registered callbacks execute
               └─→ Game state changes (e.g., "move left")

2. UPDATE PHASE
   for each GameObject:
       │
       └─→ GameObject.update(dt)
           ├─→ Apply velocity: newPos = oldPos + velocity * dt
           ├─→ Update AABB based on new position
           └─→ (Future: handle bouncing based on collisions)

3. COLLISION PHASE (optional, for debugging)
   for each pair of GameObjects:
       │
       └─→ CollisionDetector.checkAABB()
           └─→ Log/visualize collisions

4. RENDER PHASE
   window.clear()
   for each GameObject:
       │
       └─→ GameObject.render(window)
           └─→ Draw shape at current position/rotation
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
├── Makefile                    # Convenience build wrapper
├── .gitignore                  # Git ignore rules
├── README.md                   # Setup and usage instructions
│
├── src/
│   ├── main.cpp               # Entry point, creates Game
│   ├── Game.h / Game.cpp       # Main loop, window management
│   ├── GameObject.h / GameObject.cpp     # Base object class
│   ├── InputManager.h / InputManager.cpp # Input handling
│   └── CollisionDetector.h / CollisionDetector.cpp  # Collision tests
│
├── include/
│   ├── Types.h                # Shared types (AABB, ShapeType, etc.)
│   └── Constants.h            # Game constants (window size, FPS, etc.)
│
├── assets/                    # (Placeholder for later)
│   └── .gitkeep
│
└── docs/
    └── ARCHITECTURE.md        # This file
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
