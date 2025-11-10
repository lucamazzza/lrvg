/**
 * @file	object.h
 * @brief	Object class implementation
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include <string>

#include <glm/glm.hpp>

#include "common.h"

namespace lrvg {

/**
 * @brief Base class for all scene objects.
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
