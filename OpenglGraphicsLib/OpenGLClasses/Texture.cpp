//
// Created by Leonard VAN GEND on 2018/09/07.
//

#include <glad/glad.h>
#include <iostream>
#include <SDL_opengl_glext.h>
#include "Texture.hpp"
#include "openGLFunctionCallErrorManagementWrapper.hpp"

Texture::Texture(unsigned char *data, unsigned int format, int width, int height) {
	GL_ERROR_WRAPPER(glGenTextures(1, &(this->m_textureId)));
	this->bind();
	GL_ERROR_WRAPPER(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
	GL_ERROR_WRAPPER(glGenerateMipmap(GL_TEXTURE_2D));
	GL_ERROR_WRAPPER(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL_ERROR_WRAPPER(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GL_ERROR_WRAPPER(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GL_ERROR_WRAPPER(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	float anisotropicMax;
	GL_ERROR_WRAPPER(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropicMax));
	GL_ERROR_WRAPPER(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropicMax));

	this->unbind();
}

Texture::~Texture() {
	std::cout << "Texture destructor called" << std::endl;
	GL_ERROR_WRAPPER(glDeleteTextures(1, &this->m_textureId));
}

void Texture::bind() {
	GL_ERROR_WRAPPER(glBindTexture(GL_TEXTURE_2D, this->m_textureId));
}

void Texture::unbind() {
	GL_ERROR_WRAPPER(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::setActiveTextureSlot(unsigned int textureSlot) {
	GL_ERROR_WRAPPER(glActiveTexture(GL_TEXTURE0 + textureSlot));
}

void Texture::activateDefaultTextureSlot() {
	setActiveTextureSlot(0);
}

unsigned int Texture::getId() {
	return this->m_textureId;
}

Texture::Texture() {
}

Texture::Texture(const Texture &obj) {
	std::cout << "ERROR: Texture objects cannot be copied" << std::endl;
	*this = obj;
	assert(false);
}

Texture &Texture::operator=(const Texture &obj) {
	std::cout << "ERROR: Texture objects cannot be copied" << std::endl;
	this->m_textureId = obj.m_textureId;
	assert(false);
	return *this;
}
