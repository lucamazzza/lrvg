#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
DEPS_DIR="$PROJECT_ROOT/dependencies"
BUILD_DIR="$PROJECT_ROOT/.deps_build"

echo "Setting up dependencies for Linux CI..."

# Create GitLab-specific directory structure
mkdir -p "$DEPS_DIR/freeimage/lib/gitlab"
mkdir -p "$DEPS_DIR/glfw/lib/gitlab"

# Install FreeImage from system packages (much faster than building)
echo "===================================="
echo "Using system FreeImage package..."
echo "===================================="

# Create symlinks to system libraries in gitlab subfolder
if [ -f /usr/lib/x86_64-linux-gnu/libfreeimage.a ]; then
    ln -sf /usr/lib/x86_64-linux-gnu/libfreeimage.a "$DEPS_DIR/freeimage/lib/gitlab/libfreeimage.a"
elif [ -f /usr/lib/libfreeimage.a ]; then
    ln -sf /usr/lib/libfreeimage.a "$DEPS_DIR/freeimage/lib/gitlab/libfreeimage.a"
else
    echo "Warning: libfreeimage.a not found"
    exit 1
fi

echo "FreeImage linked successfully!"

# Build GLFW (fast build, ~30 seconds)
echo "===================================="
echo "Building GLFW..."
echo "===================================="

if [ ! -d "$BUILD_DIR/glfw" ]; then
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    
    echo "Downloading GLFW..."
    curl -L https://github.com/glfw/glfw/releases/download/3.3.9/glfw-3.3.9.zip -o glfw.zip
    unzip -q glfw.zip
    mv glfw-3.3.9 glfw
    rm glfw.zip
fi

cd "$BUILD_DIR/glfw"
mkdir -p build
cd build

cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DGLFW_BUILD_EXAMPLES=OFF \
    -DGLFW_BUILD_TESTS=OFF \
    -DGLFW_BUILD_DOCS=OFF

make -j$(nproc)

cp src/libglfw3.a "$DEPS_DIR/glfw/lib/gitlab/libglfw3.a"
echo "GLFW built successfully!"

echo "===================================="
echo "All dependencies set up successfully!"
echo "===================================="
