/**
 * @file	texture.h
 * @brief	Texture object class
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#define GL_TEEXTURE_MAX_ANISOTROPIC_EXT	0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x64FF

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE	0x812F
#endif

#include "common.h"
#include "object.h"

#include <glm/glm.hpp>
#include  <string>

namespace lrvg {
	class ENG_API Texture : public Object {
	public:	
		Texture(const std::string path);
		~Texture();
		void render(const glm::mat4 world_matrix) const override;
	private:
		void* bitmap;
		unsigned int texture_id;
	};
}