//
// Created by Leonard on 2018/08/29.
//

#include <glad/glad.h>
#include "VertexBuffer.hpp"
#include "openGLFunctionCallErrorManagementWrapper.hpp"

VertexBuffer::VertexBuffer(unsigned int size, void *data) {
	GL_ERROR_WRAPPER(glGenBuffers(1, &(this->m_vertexBufferId)));
	this->bind();
	GL_ERROR_WRAPPER(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	this->unbind();
}

VertexBuffer::~VertexBuffer() {
	GL_ERROR_WRAPPER(glDeleteBuffers(1, &(this->m_vertexBufferId)));
}

void VertexBuffer::bind() {
	GL_ERROR_WRAPPER(glBindBuffer(GL_ARRAY_BUFFER, this->m_vertexBufferId));
}

void VertexBuffer::unbind() {
	GL_ERROR_WRAPPER(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::VertexBuffer() {

}
