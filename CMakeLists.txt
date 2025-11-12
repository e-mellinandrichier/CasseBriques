# CMake build configuration for the CasseBriques project.
cmake_minimum_required(VERSION 3.16)

project(CasseBriques
    VERSION 0.1.0
    DESCRIPTION "SFML Brick Breaker project for learning purposes"
    LANGUAGES CXX
)

# Optionally allow the user to toggle building tests (Phase 0 focuses on the game executable).
option(CASSEBRIQUES_BUILD_TESTS "Build the CasseBriques test targets" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Try to locate SFML 3 (current Homebrew default); fall back to 2.5 if needed.
set(SFML_COMPONENTS Graphics Window System Audio)
find_package(SFML 3 COMPONENTS ${SFML_COMPONENTS} QUIET)
if (NOT SFML_FOUND)
    set(SFML_COMPONENTS system window graphics audio)
    find_package(SFML 2.5 COMPONENTS ${SFML_COMPONENTS} REQUIRED)
endif()

# Create the main executable target.
add_executable(CasseBriquesGame
    src/main.cpp
)

target_include_directories(CasseBriquesGame
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if (TARGET SFML::Graphics)
    target_link_libraries(CasseBriquesGame
        PRIVATE
            SFML::Graphics
            SFML::Window
            SFML::System
            SFML::Audio
    )
else()
    target_link_libraries(CasseBriquesGame
        PRIVATE
            sfml-graphics
            sfml-window
            sfml-system
            sfml-audio
    )
endif()

if (APPLE)
    # Copy SFML frameworks automatically when using the macOS package manager install.
    set_target_properties(CasseBriquesGame PROPERTIES
        MACOSX_BUNDLE TRUE
    )
endif()

if (CASSEBRIQUES_BUILD_TESTS)
    enable_testing()
    # Future: add test targets here (e.g., using Catch2 or doctest).
endif()

