#include "texture.h"

#include <GL/freeglut.h>
#define FREEIMAGE_LIB
#include <FreeImage.h>

/**
 * Creates a new texture by loading an image from the specified file path.
 * 
 * @param path The file path to the image to be loaded as a texture.
 */
ENG_API Texture::Texture(const std::string path) : Object() {
	FIBITMAP* bmp = FreeImage_Load(FreeImage_GetFileType(path.c_str(), 0), path.c_str());
	if (bmp == nullptr) {
		ERROR("Failed to load texture from path: " + path);
		this->bitmap = nullptr;
		return;
	}
	this->bitmap = (void*) FreeImage_ConvertTo32Bits(bmp);
	FreeImage_Unload(bmp);
	glGenTextures(1, &this->texture_id);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	const int width = FreeImage_GetWidth((FIBITMAP*)this->bitmap);
	const int height = FreeImage_GetHeight((FIBITMAP*)this->bitmap);
	glTexImage2D(GL_TEXTURE, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits((FIBITMAP*)this->bitmap));
}

/**
 * Destructor for the Texture class.
 * Cleans up the OpenGL texture and unloads the associated bitmap.
 */
ENG_API Texture::~Texture() {
	glDeleteTextures(1, &this->texture_id);
	if (this->bitmap != nullptr) {
		FreeImage_Unload((FIBITMAP*)this->bitmap);
	}
}

/**
 * Renders the texture using the provided world transformation matrix.
 * This method binds the texture and enables 2D texturing in OpenGL.
 * 
 * 
 * @param world_matrix A glm::mat4 representing the world transformation matrix.
 */
void ENG_API Texture::render(const glm::mat4 world_matrix) const {
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glEnable(GL_TEXTURE_2D);
}
