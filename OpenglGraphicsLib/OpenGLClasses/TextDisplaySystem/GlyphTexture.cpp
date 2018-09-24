//
// Created by Leonard on 2018/09/23.
//

#include <glad/glad.h>
#include <openGLFunctionCallErrorManagementWrapper.hpp>
#include "GlyphTexture.hpp"

GlyphTexture::GlyphTexture(unsigned char *data, unsigned int format, int width, int height) : Texture() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GL_ERROR_WRAPPER(glGenTextures(1, &this->m_textureId));
	this->bind();
	GL_ERROR_WRAPPER(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
	GL_ERROR_WRAPPER(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_ERROR_WRAPPER(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GL_ERROR_WRAPPER(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_ERROR_WRAPPER(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	this->unbind();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}
