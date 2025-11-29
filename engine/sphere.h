/**
 * @file	sphere.h
 * @brief	Sphere mesh class definition
 *
 * This file contains the definition of the Sphere class, which represents a sphere mesh with procedurally
 * generated geometry.
 * The Sphere class inherits from the Mesh class and allows for the creation of a sphere mesh with
 * a specified number of latitude and longitude segments.
 *
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
 * @brief Sphere mesh class with procedurally generated geometry.
 *
 * The Sphere class allows for the creation of a sphere mesh with a specified number of latitude and longitude segments.
 * The class inherits from the Mesh class and utilizes its functionality to manage vertices, normals, texture
 * coordinates, and indices.
 */
class ENG_API Sphere : public Mesh {
public:
    Sphere(int lat_segments = 20, int lon_segments = 20);
};

}
