#include "texture.h"

#include <glad/glad.h>
#define FREEIMAGE_LIB
#include <FreeImage.h>

using namespace lrvg;

/**
 * Creates a new texture by loading an image from the specified file path.
 * 
 * @param path The file path to the image to be loaded as a texture.
 */
ENG_API Texture::Texture(const std::string path) {
    FIBITMAP* bmp = nullptr;
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(path.c_str(), 0);
	if (fif == FIF_UNKNOWN) {
		fif = FreeImage_GetFIFFromFilename(path.c_str());
	}
	if (fif != FIF_UNKNOWN && FreeImage_FIFSupportsReading(fif)) {
		bmp = FreeImage_Load(fif, path.c_str());
	}
	if (bmp == nullptr) {
		ERROR("Failed to load texture from path: %s", path.c_str());
		this->bitmap = nullptr;
		this->texture_id = 0;
		return;
	}
	FIBITMAP* converted = FreeImage_ConvertTo32Bits(bmp);
	FreeImage_Unload(bmp);
	if (converted == nullptr) {
		ERROR("Failed to convert texture to 32-bit: %s", path.c_str());
		this->bitmap = nullptr;
		this->texture_id = 0;
		return;
	}
	this->bitmap = (void*)converted;
	const int width = FreeImage_GetWidth(converted);
	const int height = FreeImage_GetHeight(converted);
	BYTE* bits = FreeImage_GetBits(converted);
	if (bits == nullptr || width == 0 || height == 0) {
		ERROR("Invalid image data for texture: %s", path.c_str());
		FreeImage_Unload(converted);
		this->bitmap = nullptr;
		this->texture_id = 0;
		return;
	}
	glGenTextures(1, &this->texture_id);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
	glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * Destructor for the Texture class.
 * Cleans up the OpenGL texture and unloads the associated bitmap.
 */
ENG_API Texture::~Texture() {
	if (this->texture_id != 0) {
		glDeleteTextures(1, &this->texture_id);
		this->texture_id = 0;
	}
	if (this->bitmap != nullptr) {
		FreeImage_Unload((FIBITMAP*)this->bitmap);
		this->bitmap = nullptr;
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
    (void)world_matrix;
	if (this->texture_id == 0) return;
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
}
