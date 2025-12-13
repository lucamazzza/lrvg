/**
 * @file	material.h
 * @brief	Material object class
 *
 * This file contains the definition of the Material class, which represents a material in a 3D rendering engine.
 * A material defines the appearance of a surface, including its color properties and texture.
 * The Material class provides methods to set various color properties such as emission, ambient, diffuse,
 * and specular colors, as well as shininess and texture.
 * It also includes a render method that applies the material properties during the rendering process.
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include "common.h"
#include "object.h"
#include "texture.h"

#include <memory>
#include <glm/glm.hpp>

namespace lrvg {

/**
 * @brief Material object class.
 *
 * The Material class represents a material in a 3D rendering engine.
 * A material defines the appearance of a surface, including its color properties and texture.
 * The Material class provides methods to set various color properties such as emission, ambient, diffuse,
 * and specular colors, as well as shininess and texture.
 * It also includes a render method that applies the material properties during the rendering process.
 *
 * @see Texture
 */
class ENG_API Material : public Object {
public:
    Material();
    void set_emission_color(const glm::vec3 color);
    void set_ambient_color(const glm::vec3 color);
    void set_diffuse_color(const glm::vec3 color);
    void set_specular_color(const glm::vec3 color);
    void set_shininess(const float shininess);
    void set_texture(const std::shared_ptr<Texture> texture);
    void render(const glm::mat4 world_matrix) const override;
private:
    glm::vec3 emission_color;
    glm::vec3 ambient_color;
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;
    float shininess;
    std::shared_ptr<Texture> texture;
};

}
