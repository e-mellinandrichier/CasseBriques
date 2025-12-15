# Build instructions for CasseBriques

## Prerequisites

### macOS
```bash
# Install Homebrew (if not already installed)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake sfml
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake libsfml-dev
```

### Linux (Fedora/RHEL)
```bash
sudo dnf install gcc-c++ cmake SFML-devel
```

### Windows
1. Install [CMake](https://cmake.org/download/) (3.16 or newer)
2. Install [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/) or Visual Studio Community
3. Install SFML via one of these methods:
   - **vcpkg** (recommended):
     ```bash
     git clone https://github.com/Microsoft/vcpkg.git
     cd vcpkg
     .\vcpkg install sfml:x64-windows
     ```
   - **Manual**: Download from [SFML official site](https://www.sfml-dev.org/download/sfml/2.6.0/)

---

## Building Locally

### macOS and Linux
```bash
# Navigate to project directory
cd /path/to/CasseBriques

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build .

# Run the game
./CasseBriques
```

### Windows (Visual Studio)
```bash
# Navigate to project directory
cd C:\path\to\CasseBriques

# Create build directory
mkdir build
cd build

# Configure (adjust SFML_DIR if using custom SFML installation)
cmake .. -DSFML_DIR="C:\path\to\SFML\lib\cmake\SFML"

# Build
cmake --build . --config Release

# Run the game
.\Release\CasseBriques.exe
```

### Windows (vcpkg)
```bash
cd C:\path\to\CasseBriques
mkdir build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build . --config Release

.\Release\CasseBriques.exe
```

---

## Building with Docker

### Prerequisites
- Install [Docker](https://docs.docker.com/get-docker/)
- Install [Docker Compose](https://docs.docker.com/compose/install/) (optional, but recommended)

### Using Docker Compose (Recommended)

```bash
# Build and run
docker-compose up --build

# For GUI to work on Linux, ensure X11 forwarding:
xhost +local:docker
docker-compose up --build

# Stop the container
docker-compose down
```

### Using Docker CLI

```bash
# Build the image
docker build -t casse-briques:latest .

# Run the container (Linux with X11)
docker run -it --rm \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
  -v ~/.Xauthority:/root/.Xauthority:rw \
  casse-briques:latest

# Run on macOS (requires XQuartz)
docker run -it --rm \
  -e DISPLAY=host.docker.internal:0 \
  casse-briques:latest

# Run on Windows (WSL2)
docker run -it --rm casse-briques:latest
```

---

## Troubleshooting

### CMake not found
- **macOS**: `brew install cmake`
- **Linux**: `sudo apt-get install cmake`
- **Windows**: Reinstall CMake and ensure it's in PATH

### SFML not found
- Check that SFML is installed: `brew list sfml` (macOS) or `apt list --installed | grep sfml` (Linux)
- Rebuild with verbose output: `cmake .. -DSFML_DIR=/path/to/sfml && cmake --build . --verbose`
- Windows users: Ensure vcpkg or manual SFML installation is properly configured

### Docker X11 issues (Linux)
```bash
# Grant Docker permission to use X11
xhost +local:docker

# Then run docker-compose or docker run
```

### Docker X11 on macOS
- Install [XQuartz](https://www.xquartz.org/)
- Allow connections from network clients in XQuartz Preferences > Security
- Run: `docker run -e DISPLAY=host.docker.internal:0 casse-briques:latest`

---

## Clean Build

```bash
# Remove build artifacts
rm -rf build/

# Rebuild from scratch
mkdir build
cd build
cmake ..
cmake --build .
```

## Docker Clean Build

```bash
# Remove old image
docker rmi casse-briques:latest

# Rebuild
docker build -t casse-briques:latest .
```
