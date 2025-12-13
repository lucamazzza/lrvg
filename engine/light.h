/**
 * @file	light.h
 * @brief	Light class definition
 *
 * This file contains the definition of the Light class, which serves as a base class for different types of light sources
 * in a 3D rendering engine. The Light class provides common functionality for managing light properties such as ambient,
 * diffuse, and specular colors. It also handles the assignment of unique light IDs for OpenGL light sources.
 * Derived classes must implement the render method to define their specific rendering behavior.
 * Lights are essential for illuminating scenes in 3D graphics applications.
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include "common.h"
#include "node.h"

namespace lrvg {

/**
 * @brief Light source node base class. A light illuminates every object it can "see".
 *
 * The Light class is an abstract base class that inherits from Node.
 * It provides common functionality for different types of light sources, such as point lights and directional lights
 * The class manages properties like ambient, diffuse, and specular colors.
 * It also defines a pure virtual render method that must be implemented by derived classes.
 * Lights are essential for illuminating scenes in 3D graphics applications.
 *
 * @see Node
 */
class ENG_API Light : public Node {
public:
    Light();
    int get_priority() const override;
    void set_ambient_color(const glm::vec3 color);
    void set_diffuse_color(const glm::vec3 color);
    void set_specular_color(const glm::vec3 color);
    virtual void render(const glm::mat4 world_matrix) const override = 0;
protected:
    int light_id;
    glm::vec3 ambient_color;
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;
    int get_current_light(const int light_id) const;
    static int next_light_id;
};

}
