Build Scripts
=============

build_dependencies.sh
---------------------

    This script downloads and builds the GLFW and FreeImage libraries from source for Linux.

    What it does
    ------------
        
        * Downloads GLFW 3.3.9 from GitHub
        * Downloads FreeImage 3.18.0 from SourceForge
        * Builds both libraries using CMake (GLFW) and Make (FreeImage)
        * Copies the resulting static libraries to `dependencies/glfw/lib/lin/` and `dependencies/freeimage/lib/lin/`

    Requirements
    ------------
        
        * make
        * cmake
        * unzip
        * curl
        * Standard development tools (gcc, g++, ar)
        * OpenGL development libraries (libgl1-mesa-dev on Ubuntu/Debian)
        * X11 development libraries (libx11-dev, libxrandr-dev, libxinerama-dev, libxcursor-dev, libxi-dev)


    Notes
    -----
        
        * The script creates a `.deps_build` directory for temporary build files
        * Source code is cached in `.deps_build` to speed up subsequent builds
        * The script is automatically run by the GitLab CI pipeline for every build
