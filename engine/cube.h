/**
 * @file	cube.h
 * @brief	Cube mesh class definition
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
 * @brief Cube mesh class.
 */
class ENG_API Cube : public Mesh {
public:
    Cube(int segments = 40);
};

}
