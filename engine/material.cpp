/**
 * @file    material.cpp	
 * @brief   Light class implementation
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "material.h"

#include <memory>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"

using namespace lrvg;

/**
 * Creates a new instance of Material with default color and texture properties.
 * Default properties:
 * * Emission Color: (0.0, 0.0, 0.0)
 * * Ambient Color: (0.75, 0.75, 0.75)
 * * Diffuse Color: (0.75, 0.75, 0.75)
 * * Specular Color: (0.75, 0.75, 0.75)
 * * Shininess: 64.0
 * * Texture: nullptr (no texture)
 */
ENG_API Material::Material() : Object() {
	this->set_emission_color(glm::vec3(0.0f, 0.0f, 0.0f));
	this->set_ambient_color(glm::vec3(0.2f, 0.2f, 0.2f));
	this->set_diffuse_color(glm::vec3(0.8f, 0.8f, 0.8f));
	this->set_specular_color(glm::vec3(0.5f, 0.5f, 0.5f));
	this->set_shininess(128.0f);
	this->set_texture(nullptr);
}

/**
 * Sets the emission color of the material.
 * 
 * @param color A glm::vec3 representing the emission color.
 */
void ENG_API Material::set_emission_color(const glm::vec3 color) {
	this->emission_color = color;
}

/**
 * Sets the ambient color of the material.
 * 
 * @param color A glm::vec3 representing the ambient color.
 */
void ENG_API Material::set_ambient_color(const glm::vec3 color) {
	this->ambient_color = color;
}

/**
 * Sets the diffuse color of the material.
 * 
 * @param color A glm::vec3 representing the diffuse color.
 */
void ENG_API Material::set_diffuse_color(const glm::vec3 color) {
	this->diffuse_color = color;
}

/**
 * Sets the specular color of the material.
 * 
 * @param color A glm::vec3 representing the specular color.
 */
void ENG_API Material::set_specular_color(const glm::vec3 color) {
	this->specular_color = color;
}

/**
 * Sets the shininess of the material.
 * 
 * @param shininess A float representing the shininess value.
 */
void ENG_API Material::set_shininess(const float shininess) {
	this->shininess = shininess;
}

/**
 * Sets the texture of the material.
 * 
 * @param texture A shared pointer to the Texture object to be used.
 */
void ENG_API Material::set_texture(const std::shared_ptr<Texture> texture) {
	this->texture = texture;
}

/**
 * Renders the material using the provided world transformation matrix.
 * This method sets the OpenGL material properties and binds the texture if available.
 *
 * This method is called automatically during the rendering process.
 * 
 * @param world_matrix A glm::mat4 representing the world transformation matrix.
 */
void ENG_API Material::render(const glm::mat4 world_matrix) const {
    glDisable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  glm::value_ptr(glm::vec4(this->emission_color, 1.0f)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   glm::value_ptr(glm::vec4(this->ambient_color, 1.0f)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   glm::value_ptr(glm::vec4(this->diffuse_color, 1.0f)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  glm::value_ptr(glm::vec4(this->specular_color, 1.0f)));
	glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, this->shininess);
	if (this->texture != nullptr) {
		this->texture->render(world_matrix);
	}
}
