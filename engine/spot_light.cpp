/**
 * @file	spot_light.cpp
 * @brief	Spot light class implementation
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "spot_light.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "common.h"
#include "node.h"

using namespace lrvg;

/**
 * Creates a spot light with default parameters.
 * 
 * * Direction: 0.0f, 1.0f, 0.0f (down)
 * * Cutoff: 45.0f
 * * Exponent: 8.0f
 * * Radius: 1.0f
 */
ENG_API SpotLight::SpotLight() {
	this->set_direction(glm::vec3(0.0f, 1.0f, 0.0f));
	this->set_cutoff(45.0f);
	this->set_exponent(8.0f);
	this->set_radius(1.0f);
}

/**
 * Sets the light direction.
 * It is also possible to set the direction using the node rotation.
 * 
 * @param direction new light direction
 */
void ENG_API SpotLight::set_direction(const glm::vec3 direction) {
	this->direction = direction;
}

/**
 * Sets the light cutoff angle (in degrees).
 * The cutoff angle defines the maximum spread angle of the light.
 * 
 * @see https://gdbooks.gitbooks.io/legacyopengl/content/Chapter5/light_spotlight.html
 * 
 * @param cutoff new cutoff angle
 */
void ENG_API SpotLight::set_cutoff(const float cutoff) {
	this->cutoff = cutoff;
}

/**
 * Sets the light exponent.
 * The exponent defines how the light intensity decreases from the center to the edges of the spotlight.
 * 
 * @see https://gdbooks.gitbooks.io/legacyopengl/content/Chapter5/light_spotlight.html
 * 
 * @param exponent new exponent
 */
void ENG_API SpotLight::set_exponent(const float exponent) {
	this->exponent = exponent;
}

/**
 * Sets the light radius.
 * The radius defines how quickly the light intensity decreases with distance.
 * 
 * @param radius new radius
 */
void ENG_API SpotLight::set_radius(const float radius) {
	this->radius = radius;
}

/**
 * Renders the spot light.
 * 
 * This method is automatically called by the engine when rendering the scene.
 * 
 * @param world_matrix world transformation matrix
 */
void ENG_API SpotLight::render(const glm::mat4 world_matrix) const {
	Node::render(world_matrix);
	glEnable(GL_LIGHT0 + this->light_id);
	const glm::vec4 light_pos(this->direction, 1.0f);
	const glm::vec3 light_dir(this->direction);
	const glm::vec4 ambient(this->ambient_color, 1.0f);
	const glm::vec4 diffuse(this->diffuse_color, 1.0f);
	const glm::vec4 specular(this->specular_color, 1.0f);
	const float const_attenuation = 1.0f / this->radius;
	const int cur_light = Light::get_current_light(this->light_id);
	glLightfv(cur_light, GL_POSITION, glm::value_ptr(light_pos));
	glLightfv(cur_light, GL_SPOT_DIRECTION, glm::value_ptr(light_dir));
	glLightfv(cur_light, GL_AMBIENT, glm::value_ptr(ambient));
	glLightfv(cur_light, GL_DIFFUSE, glm::value_ptr(diffuse));
	glLightfv(cur_light, GL_SPECULAR, glm::value_ptr(specular));
	glLightfv(cur_light, GL_SPOT_CUTOFF, &this->cutoff);
	glLightf(cur_light, GL_CONSTANT_ATTENUATION, const_attenuation);
	glLightf(cur_light, GL_SPOT_EXPONENT, this->exponent);
}
