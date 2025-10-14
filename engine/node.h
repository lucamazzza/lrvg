/**
 * @file	node.h
 * @brief	TODO:
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "common.h"
#include "object.h"

/**
 * @brief Scene graph node class.
 */
class ENG_API Node : public Object {
public:
	Node();
	void set_base_matrix(const glm::mat4 base_matrix);
	void set_position(const glm::vec3 position);
	void set_rotation(const glm::vec3 rotation);
	void set_scale(const glm::vec3 scale);
	glm::mat4 get_local_matrix() const override;
	glm::vec3 get_position() const;
	glm::vec3 get_rotation() const;
	glm::vec3 get_scale() const;
	void render(const glm::mat4 world_matrix) const override;
private:
	glm::mat4 base_matrix;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};
