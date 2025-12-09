cmake_minimum_required(VERSION 3.16)
project(BreakOut LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouve SFML 2.5 ou plus récent (2.6.1 dans ton cas)
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Ajoute les fichiers sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Crée l’exécutable
add_executable(BreakOut ${SOURCES})

# Include headers
target_include_directories(BreakOut PRIVATE include)

# Lie SFML
target_link_libraries(BreakOut PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

# Option linker pour Windows GUI (évite l’erreur WinMain manquant)
#target_link_options(BreakOut PRIVATE "-mwindows")

# Copie le dossier assets dans le dossier build
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Optionnel : tests
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
