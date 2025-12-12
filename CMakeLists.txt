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

# Try to locate SFML 2.6.1 (or compatible 2.6.x version)
# On macOS with Homebrew, sfml@2 is keg-only, so we need to set CMAKE_PREFIX_PATH
if (APPLE)
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/opt/homebrew/opt/sfml@2")
endif()

set(SFML_COMPONENTS system window graphics audio)
find_package(SFML 2.6.1 COMPONENTS ${SFML_COMPONENTS} QUIET)
if (NOT SFML_FOUND)
    # Fall back to any 2.6.x version if 2.6.1 not found
    find_package(SFML 2.6 COMPONENTS ${SFML_COMPONENTS} REQUIRED)
endif()

# Create the main executable target.
add_executable(CasseBriquesGame
    src/main.cpp
    src/GameObject.cpp
    src/InputManager.cpp
    src/Brick.cpp
    src/Paddle.cpp
    src/Ball.cpp
    src/Menu.cpp
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
    # Configure macOS app bundle properties
    set_target_properties(CasseBriquesGame PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "CasseBriques"
        MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.cassebriques.game"
        MACOSX_BUNDLE_INFO_STRING "CasseBriques ${PROJECT_VERSION}"
        MACOSX_BUNDLE_COPYRIGHT "Copyright © 2024"
    )
    
    # Set rpath to look for frameworks in the app bundle
    set_target_properties(CasseBriquesGame PROPERTIES
        INSTALL_RPATH "@executable_path/../Frameworks"
        BUILD_WITH_INSTALL_RPATH TRUE
    )
    
    # Set SFML frameworks directory (where we installed SFML 2.6.1)
    set(SFML_FRAMEWORKS_DIR "/opt/homebrew/opt/sfml@2/lib")
    
    # Copy SFML frameworks and dylibs into the app bundle
    add_custom_command(TARGET CasseBriquesGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks"
        # Copy frameworks
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_FRAMEWORKS_DIR}/OpenAL.framework"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/OpenAL.framework"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_FRAMEWORKS_DIR}/FLAC.framework"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/FLAC.framework"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_FRAMEWORKS_DIR}/ogg.framework"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/ogg.framework"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_FRAMEWORKS_DIR}/vorbis.framework"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/vorbis.framework"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_FRAMEWORKS_DIR}/vorbisenc.framework"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/vorbisenc.framework"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_FRAMEWORKS_DIR}/vorbisfile.framework"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/vorbisfile.framework"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_FRAMEWORKS_DIR}/freetype.framework"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/freetype.framework"
        # Copy SFML dylibs
        COMMAND ${CMAKE_COMMAND} -E copy
            "${SFML_FRAMEWORKS_DIR}/libsfml-system.2.6.1.dylib"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/libsfml-system.2.6.dylib"
        COMMAND ${CMAKE_COMMAND} -E copy
            "${SFML_FRAMEWORKS_DIR}/libsfml-window.2.6.1.dylib"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/libsfml-window.2.6.dylib"
        COMMAND ${CMAKE_COMMAND} -E copy
            "${SFML_FRAMEWORKS_DIR}/libsfml-graphics.2.6.1.dylib"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/libsfml-graphics.2.6.dylib"
        COMMAND ${CMAKE_COMMAND} -E copy
            "${SFML_FRAMEWORKS_DIR}/libsfml-audio.2.6.1.dylib"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/libsfml-audio.2.6.dylib"
        # Update rpaths in SFML dylibs to point to frameworks in app bundle
        COMMAND install_name_tool -add_rpath "@loader_path"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/libsfml-system.2.6.dylib"
        COMMAND install_name_tool -add_rpath "@loader_path"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/libsfml-window.2.6.dylib"
        COMMAND install_name_tool -add_rpath "@loader_path"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/libsfml-graphics.2.6.dylib"
        COMMAND install_name_tool -add_rpath "@loader_path"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/libsfml-audio.2.6.dylib"
        # Update executable to load SFML dylibs from app bundle
        COMMAND install_name_tool -change
            "${SFML_FRAMEWORKS_DIR}/libsfml-system.2.6.1.dylib"
            "@rpath/libsfml-system.2.6.dylib"
            "$<TARGET_FILE:CasseBriquesGame>"
        COMMAND install_name_tool -change
            "${SFML_FRAMEWORKS_DIR}/libsfml-window.2.6.1.dylib"
            "@rpath/libsfml-window.2.6.dylib"
            "$<TARGET_FILE:CasseBriquesGame>"
        COMMAND install_name_tool -change
            "${SFML_FRAMEWORKS_DIR}/libsfml-graphics.2.6.1.dylib"
            "@rpath/libsfml-graphics.2.6.dylib"
            "$<TARGET_FILE:CasseBriquesGame>"
        COMMAND install_name_tool -change
            "${SFML_FRAMEWORKS_DIR}/libsfml-audio.2.6.1.dylib"
            "@rpath/libsfml-audio.2.6.dylib"
            "$<TARGET_FILE:CasseBriquesGame>"
        # Update SFML dylibs to reference each other from app bundle
        COMMAND install_name_tool -change
            "${SFML_FRAMEWORKS_DIR}/libsfml-system.2.6.1.dylib"
            "@rpath/libsfml-system.2.6.dylib"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/libsfml-window.2.6.dylib"
        COMMAND install_name_tool -change
            "${SFML_FRAMEWORKS_DIR}/libsfml-system.2.6.1.dylib"
            "@rpath/libsfml-system.2.6.dylib"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/libsfml-graphics.2.6.dylib"
        COMMAND install_name_tool -change
            "${SFML_FRAMEWORKS_DIR}/libsfml-system.2.6.1.dylib"
            "@rpath/libsfml-system.2.6.dylib"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/libsfml-audio.2.6.dylib"
        COMMAND install_name_tool -change
            "${SFML_FRAMEWORKS_DIR}/libsfml-window.2.6.1.dylib"
            "@rpath/libsfml-window.2.6.dylib"
            "$<TARGET_FILE_DIR:CasseBriquesGame>/../Frameworks/libsfml-graphics.2.6.dylib"
        # Remove quarantine attribute to allow execution (macOS security)
        COMMAND xattr -cr "$<TARGET_FILE_DIR:CasseBriquesGame>/../.."
        COMMENT "Copying SFML frameworks and libraries to app bundle"
    )
endif()

if (CASSEBRIQUES_BUILD_TESTS)
    enable_testing()
    # Future: add test targets here (e.g., using Catch2 or doctest).
endif()

