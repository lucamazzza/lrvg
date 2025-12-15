HANOI TOWER GAME - Release Package
===================================

CONTENTS:
---------
- hanoi              : Main executable
- libengine.dylib    : Graphics engine library
- HanoiBased.ovo     : 3D scene file
- *.dds              : Texture files (14 files)

HOW TO RUN:
-----------
Extract the package and run from the extracted directory:
    tar -xzf hanoi.tar.gz
    cd hanoi
    ./hanoi

CONTROLS:
---------
[1-3]   Select Tower (source then target)
[S]     Auto-solve
[R]     Restart game
[P]     Perspective camera
[O]     Ortho camera
[A/D]   Rotate camera around the scene
[J]     Zoom - (ortho)
[K]     Zoom + (ortho)

REQUIREMENTS:
-------------
- macOS (ARM64) or Linux x86_64
- OpenGL support

NOTE:
-----
All files must remain in the same directory for the application to work correctly.
The executable uses @executable_path (macOS) or $ORIGIN (Linux) to locate the library at runtime.

Build Date: 20251215
