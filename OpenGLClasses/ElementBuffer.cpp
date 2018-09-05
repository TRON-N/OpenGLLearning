//
// Created by Leonard on 2018/08/29.
//

#include <glad/glad.h>
#include "ElementBuffer.hpp"
#include "openGLFunctionCallErrorManagementWrapper.hpp"

ElementBuffer::ElementBuffer(unsigned int size, void *data, int drawOption) {
	GL_ERROR_WRAPPER(glGenBuffers(1, &(this->m_elementBufferId)));
	this->m_dataSize = size;
	this->m_data = data;
	this->m_drawOption = drawOption;
}

ElementBuffer::~ElementBuffer() {
	GL_ERROR_WRAPPER(glDeleteBuffers(1, &(this->m_elementBufferId)));
}

void ElementBuffer::setUpForVertexArray() {
	this->bind();
	GL_ERROR_WRAPPER(glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_dataSize, this->m_data, this->m_drawOption));
}

void ElementBuffer::bind() {
	GL_ERROR_WRAPPER(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_elementBufferId));
}

void ElementBuffer::unbind() {
	GL_ERROR_WRAPPER(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

ElementBuffer::ElementBuffer() {

}


