#ifndef CONSTANTS_H
#define CONSTANTS_H

// window constants
namespace Constants
{
    // window dimensions
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;
    constexpr const char* WINDOW_TITLE = "CasseBriques - Step 1: Game Engine";

    // game loop
    constexpr float TARGET_FPS = 60.0f;
    constexpr float FRAME_TIME = 1.0f / TARGET_FPS; // ~16.67 ms

    // colours (SFML uses RGBA)
    constexpr unsigned int COLOR_WHITE = 0xFFFFFFFF;
    constexpr unsigned int COLOR_BLACK = 0x000000FF;
    constexpr unsigned int COLOR_RED = 0xFF0000FF;
    constexpr unsigned int COLOR_GREEN = 0x00FF00FF;
    constexpr unsigned int COLOR_BLUE = 0x0000FFFF;
    constexpr unsigned int COLOR_YELLOW = 0xFFFF00FF;

    // physics
    constexpr float GRAVITY = 0.0f; // No gravity in Step 1
    constexpr float DAMPING = 1.0f; // No damping in Step 1

    // debug
    constexpr bool DEBUG_COLLISION = true;  // draw collision boxes
    constexpr bool DEBUG_FPS = true;        // show FPS counter
}

#endif // CONSTANTS_H
