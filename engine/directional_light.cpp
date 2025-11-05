/**
 * @file	directional_light.h
 * @brief	Directional light class implementation
 * 
 * @author	Luca Mazza i        (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "directional_light.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "common.h"
#include "node.h"

using namespace lrvg;

/**
 * Creates a directional light with default parameters.
 * 
 * * Direction: 0.0f, 1.0f, 0.0f (down)
 */
ENG_API DirectionalLight::DirectionalLight() {
	this->direction = glm::vec3(0.0f, 1.0f, 0.0f);
}

/**
 * Sets the light direction.
 * It is also possible to set the direction using the node rotation.
 * 
 * @param direction new light direction
 */
void ENG_API DirectionalLight::set_direction(const glm::vec3 direction) {
	this->direction = direction;
}

/**
 * Renders the directional light.
 * 
 * This method is automatically called by the engine when rendering the scene.
 * 
 * @param world_matrix world transformation matrix
 */
void ENG_API DirectionalLight::render(const glm::mat4 world_matrix) const {
	Node::render(world_matrix);
	glEnable(GL_LIGHT0 + this->light_id);
	const glm::vec4 light_pos(this->direction, 0.0f);
	const glm::vec4 ambient(this->ambient_color, 1.0f);
	const glm::vec4 diffuse(this->diffuse_color, 1.0f);
	const glm::vec4 specular(this->specular_color, 1.0f);
	const int cur_light = Light::get_current_light(this->light_id);
	glLightfv(cur_light, GL_POSITION,   glm::value_ptr(light_pos));
	glLightfv(cur_light, GL_AMBIENT,    glm::value_ptr(ambient));
	glLightfv(cur_light, GL_DIFFUSE,    glm::value_ptr(diffuse));
	glLightfv(cur_light, GL_SPECULAR,   glm::value_ptr(specular));
}
