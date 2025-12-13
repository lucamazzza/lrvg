/**
 * @file	directional_light.h
 * @brief	Directional light class definition
 *
 * This file contains the definition of the DirectionalLight class, which represents a directional light source 
 * in a 3D rendering engine. A directional light simulates light coming from a specific direction,
 * similar to sunlight, affecting all objects in the scene uniformly.
 * The DirectionalLight class inherits from the Light base class and provides methods to set the direction
 * of the light and to render the light's effect on the scene.
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include <glm/glm.hpp>

#include "common.h"
#include "light.h"

namespace lrvg {

/**
 * @brief Directional light class. A directional light simulates light coming from a specific direction,
 * similar to sunlight, affecting all objects in the scene uniformly.
 *
 * The DirectionalLight class inherits from the Light base class and represents a light source that emits
 * parallel light rays in a specified direction. This type of light is commonly used to simulate sunlight
 * or other distant light sources in 3D graphics applications. The class provides methods to set the direction
 * of the light and to render the light's effect on the scene.
 *
 * @see Light
 */
class ENG_API DirectionalLight : public Light {
public:
    DirectionalLight();
    void set_direction(const glm::vec3 direction);
    void render(const glm::mat4 world_matrix) const override;
private:
    glm::vec3 direction;
};

}
