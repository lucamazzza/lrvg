/**
 * @file	cube.h
 * @brief	Cube mesh class definition
 *
 * This file contains the definition of the Cube class, which represents a cube mesh with six faces and procedurally 
 * generated geometry. 
 * The Cube class inherits from the Mesh class and allows for the creation of a cube mesh with a specified number
 * of subdivisions per face.
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include "common.h"
#include "mesh.h"

namespace lrvg {

/**
 * @brief Cube mesh class with six faces and procedurally generated geometry.
 *
 * The Cube class allows for the creation of a cube mesh with a specified number of subdivisions per face.
 * Each face of the cube is made up of smaller quads based on the number of segments provided.
 * The cube is centered at the origin and extends from -0.5 to +0.5 along each axis.
 * The class inherits from the Mesh class and utilizes its functionality to manage vertices, normals, texture 
 * coordinates, and indices.
 */
class ENG_API Cube : public Mesh {
public:
    Cube(int segments = 40);
};

}
