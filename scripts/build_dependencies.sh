#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
DEPS_DIR="$PROJECT_ROOT/dependencies"

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

# Install GLFW from system packages
echo "===================================="
echo "Using system GLFW package..."
echo "===================================="

if [ -f /usr/lib/x86_64-linux-gnu/libglfw3.a ]; then
    ln -sf /usr/lib/x86_64-linux-gnu/libglfw3.a "$DEPS_DIR/glfw/lib/gitlab/libglfw3.a"
elif [ -f /usr/lib/libglfw3.a ]; then
    ln -sf /usr/lib/libglfw3.a "$DEPS_DIR/glfw/lib/gitlab/libglfw3.a"
else
    echo "Warning: libglfw3.a not found"
    exit 1
fi

echo "GLFW linked successfully!"

echo "===================================="
echo "All dependencies set up successfully!"
echo "===================================="
