#pragma once

#include "common.h"
#include "node.h"

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
protected:
	glm::vec3 ambient_color;
	glm::vec3 diffuse_color;
	glm::vec3 specular_color;
	int get_current_light(const int light_id) const;
	static int next_light_id;
	int light_id;
};
