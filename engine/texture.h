/**
 * @file	texture.h
 * @brief	TODO:
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#define GL_TEXTURE_MAX_ANISOTROPY_EXT		0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT	0x84FF

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE					0x812F
#endif

#include <string>

#include <glm/glm.hpp>

#include "common.h"
#include "object.h"

/**
 * @brief Texture object class.
 */
class ENG_API Texture : public Object {
public:
	Texture(const std::string path);
	~Texture();
	void render(const glm::mat4 world_matrix) const override;
private:
	void* bitmap;
	unsigned int texture_id;
};
