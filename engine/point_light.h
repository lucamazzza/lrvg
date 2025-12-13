/**
 * @file	point_light.h
 * @brief	Point light class definition
 *
 * This file contains the definition of the PointLight class, which represents a point light source in a 3D scene.
 * A point light emits light uniformly in all directions from a single point in space.
 * The PointLight class inherits from the Light class and provides methods to set the light's position
 * and to render the light in the scene.
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include "common.h"
#include "light.h"

namespace lrvg {

/**
 * @brief Point light class.
 *
 * The PointLight class represents a point light source in a 3D scene.
 * A point light emits light uniformly in all directions from a single point in space.
 * The PointLight class inherits from the Light class and provides methods to set the light's position
 * and to render the light in the scene.
 *
 * @see Light
 */
class ENG_API PointLight : public Light {
public:
    PointLight();
    void set_radius(const float radius);
    void render(const glm::mat4 world_matrix) const override;
private:
    float radius;
};

}
