/**
 * @file	material.h
 * @brief	Material object class
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include "common.h"
#include "object.h"
#include "texture.h"

#include <memory>
#include <glm/glm.hpp>

namespace lrvg {
	class ENG_API Material : public Object {
	public:
		Material();
		void set_emission_color(const glm::vec3 color);
		void set_ambient_color(const glm::vec3 color);
		void set_diffuse_color(const glm::vec3 color);
		void set_specular_color(const glm::vec3 color);
		void set_shininess(const float shininess);
		void set_texture(const std::shared_ptr<Texture> texture);
		void render(const glm::mat4 world_matrix) const override;
	private:
		glm::vec3 emission_color;
		glm::vec3 ambient_color;
		glm::vec3 diffuse_color;
		glm::vec3 specular_color;
		float shininess;
		std::shared_ptr<Texture> texture;
	};
}