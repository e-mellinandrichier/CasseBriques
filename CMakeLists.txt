cmake_minimum_required(VERSION 3.16)
project(CasseBriques)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(CasseBriques 
    src/main.cpp
    src/Game.cpp
    src/GameObject.cpp
    src/InputManager.cpp
    src/CollisionDetector.cpp
)

target_include_directories(CasseBriques PRIVATE include)
target_link_libraries(CasseBriques PRIVATE sfml-graphics sfml-window sfml-system)
