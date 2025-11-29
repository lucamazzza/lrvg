/**
 * @file	plane.h
 * @brief	Plane mesh class definition
 *
 * This file contains the definition of the Plane class, which represents a plane mesh with procedurally
 * generated geometry.
 * The Plane class inherits from the Mesh class and allows for the creation of a plane mesh with
 * a specified number of subdivisions.
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
 * @brief Plane mesh class lying on the XZ plane with procedurally generated geometry.
 *
 * The Plane class allows for the creation of a plane mesh with a specified number of subdivisions along each axis.
 * The plane is centered at the origin and lies on the XZ plane, extending from -1 to +1 in both X and Z dimensions.
 * The class inherits from the Mesh class and utilizes its functionality to manage vertices, normals, texture 
 * coordinates, and indices.
 */
class ENG_API Plane : public Mesh {
public:
    Plane(int segments = 80);
};

}
