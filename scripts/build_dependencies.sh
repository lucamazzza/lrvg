#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
DEPS_DIR="$PROJECT_ROOT/dependencies"

echo "Setting up dependencies for Linux..."

mkdir -p "$DEPS_DIR"

# Install FreeImage from system packages (much faster than building)
echo "===================================="
echo "Using system FreeImage package..."
echo "===================================="
# Already installed via apt-get in gitlab-ci.yml
mkdir -p "$DEPS_DIR/freeimage/lib/lin"
mkdir -p "$DEPS_DIR/freeimage/include"

# Create symlinks to system libraries
if [ -f /usr/lib/x86_64-linux-gnu/libfreeimage.a ]; then
    ln -sf /usr/lib/x86_64-linux-gnu/libfreeimage.a "$DEPS_DIR/freeimage/lib/lin/libfreeimage.a"
elif [ -f /usr/lib/libfreeimage.a ]; then
    ln -sf /usr/lib/libfreeimage.a "$DEPS_DIR/freeimage/lib/lin/libfreeimage.a"
else
    echo "Warning: libfreeimage.a not found, using shared library instead"
    if [ -f /usr/lib/x86_64-linux-gnu/libfreeimage.so ]; then
        ln -sf /usr/lib/x86_64-linux-gnu/libfreeimage.so "$DEPS_DIR/freeimage/lib/lin/libfreeimage.so"
    fi
fi

if [ -f /usr/include/FreeImage.h ]; then
    ln -sf /usr/include/FreeImage.h "$DEPS_DIR/freeimage/include/FreeImage.h"
fi

echo "FreeImage linked successfully!"

# Install GLFW from system packages
echo "===================================="
echo "Using system GLFW package..."
echo "===================================="
mkdir -p "$DEPS_DIR/glfw/lib/lin"
mkdir -p "$DEPS_DIR/glfw/include"

if [ -f /usr/lib/x86_64-linux-gnu/libglfw3.a ]; then
    ln -sf /usr/lib/x86_64-linux-gnu/libglfw3.a "$DEPS_DIR/glfw/lib/lin/libglfw3.a"
elif [ -f /usr/lib/libglfw3.a ]; then
    ln -sf /usr/lib/libglfw3.a "$DEPS_DIR/glfw/lib/lin/libglfw3.a"
fi

echo "GLFW linked successfully!"

echo "===================================="
echo "All dependencies set up successfully!"
echo "===================================="
