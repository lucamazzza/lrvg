/**
 * @file	object.h
 * @brief	Object class definition
 *
 * This file contains the definition of the Object class, which serves as the base class for all objects in the scene.
 * It provides a unique identifier (ID) and a name for each object.
 * The class also defines virtual methods for retrieving the local transformation matrix,
 * getting the rendering priority, and rendering the object.
 * Derived classes must implement the render method to define their specific rendering behavior.
 * This class is essential for managing and organizing objects within the graphics engine.
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include <string>

#include <glm/glm.hpp>

#include "common.h"

namespace lrvg {

/**
 * @brief Base class for all scene objects.
 *
 * The Object class serves as the base class for all objects in the scene.
 * It provides a unique identifier (ID) and a name for each object.
 * The class also defines virtual methods for retrieving the local transformation matrix,
 * getting the rendering priority, and rendering the object.
 * Derived classes must implement the render method to define their specific rendering behavior.
 * This class is essential for managing and organizing objects within the graphics engine.
 */
class ENG_API Object {
public:
	Object();
	Object(const std::string name);
    virtual ~Object() = default;
	int get_id() const;
    std::string get_name() const;
    void set_name(const std::string name);
	virtual glm::mat4 get_local_matrix() const;
	virtual int get_priority() const;
	virtual void render(const glm::mat4 world_matrix) const = 0;
private:
	static int next_id;
	int id;
	std::string name;
};

}
