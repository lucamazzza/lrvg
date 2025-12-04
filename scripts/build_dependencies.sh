#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
DEPS_DIR="$PROJECT_ROOT/dependencies"
BUILD_DIR="$PROJECT_ROOT/.deps_build"

echo "Building dependencies for Linux..."

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Detect number of CPU cores for parallel builds
NPROC=$(nproc 2>/dev/null || echo 4)

# Build GLFW
echo "===================================="
echo "Building GLFW..."
echo "===================================="
if [ ! -d "glfw" ]; then
    echo "Downloading GLFW..."
    curl -L https://github.com/glfw/glfw/releases/download/3.3.9/glfw-3.3.9.zip -o glfw.zip
    unzip -q glfw.zip
    mv glfw-3.3.9 glfw
    rm glfw.zip
fi

cd glfw
mkdir -p build
cd build

cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DGLFW_BUILD_EXAMPLES=OFF \
    -DGLFW_BUILD_TESTS=OFF \
    -DGLFW_BUILD_DOCS=OFF

make -j$NPROC

mkdir -p "$DEPS_DIR/glfw/lib/lin"
cp src/libglfw3.a "$DEPS_DIR/glfw/lib/lin/libglfw3.a"
echo "GLFW built successfully!"

# Build FreeImage
cd "$BUILD_DIR"
echo "===================================="
echo "Building FreeImage..."
echo "===================================="
if [ ! -d "freeimage" ]; then
    echo "Downloading FreeImage..."
    curl -L https://downloads.sourceforge.net/project/freeimage/Source%20Distribution/3.18.0/FreeImage3180.zip -o FreeImage.zip
    unzip -q FreeImage.zip
    mv FreeImage freeimage
    rm FreeImage.zip
fi

cd freeimage

# Compile FreeImage with C++14 to avoid C++17 compatibility issues
echo "Building FreeImage with C++14..."
CXXFLAGS="-O3 -fPIC -fexceptions -fvisibility=hidden -Wno-ctor-dtor-privacy -std=c++14" make -j$NPROC -f Makefile.gnu

mkdir -p "$DEPS_DIR/freeimage/lib/lin"
cp Dist/libfreeimage.a "$DEPS_DIR/freeimage/lib/lin/libfreeimage.a"
echo "FreeImage built successfully!"

echo "===================================="
echo "All dependencies built successfully!"
echo "===================================="
