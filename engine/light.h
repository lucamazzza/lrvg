/**
 * @file	light.h
 * @brief	TODO:
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include "common.h"
#include "node.h"

namespace lrvg {

/**
 * @brief Light source node base class. A light illuminates every object it can "see".
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
