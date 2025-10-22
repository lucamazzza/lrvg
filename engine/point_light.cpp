#include "point_light.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.h"
#include "node.h"

using namespace lrvg;

/**
 * Creates a point light with default parameters.
 * 
 * * Radius: 1.0f
 */
ENG_API PointLight::PointLight() : Light() {
	this->set_radius(1.0f);
}

/**
 * Sets the light radius.
 * The radius defines how the light intensity decreases with distance.
 * 
 * @param radius new radius
 */
void ENG_API PointLight::set_radius(const float radius) {
	this->radius = radius;
}

/**
 * Renders the point light.
 * 
 * This method is automatically called by the engine when rendering the scene.
 * 
 * @param world_matrix world transformation matrix
 */
void ENG_API PointLight::render(const glm::mat4 world_matrix) const {
	Node::render(world_matrix);
	glEnable(GL_LIGHT0 + this->light_id);
	const glm::vec4 light_pos = world_matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	const glm::vec4 ambient(this->ambient_color, 1.0f);
	const glm::vec4 diffuse(this->diffuse_color, 1.0f);
	const glm::vec4 specular(this->specular_color, 1.0f);
	constexpr float cutoff = 180.0f;
	const float const_attenuation = 1.0f / this->radius;
	const int cur_light = Light::get_current_light(this->light_id);
	glLightfv(cur_light, GL_POSITION, glm::value_ptr(light_pos));
	glLightfv(cur_light, GL_AMBIENT, glm::value_ptr(ambient));
	glLightfv(cur_light, GL_DIFFUSE, glm::value_ptr(diffuse));
	glLightfv(cur_light, GL_SPECULAR, glm::value_ptr(specular));
	glLightfv(cur_light, GL_SPOT_CUTOFF, &cutoff);
	glLightf(cur_light, GL_CONSTANT_ATTENUATION, const_attenuation);
}
