//
// Created by Leonard on 2018/08/29.
//

#include <glad/glad.h>
#include "VertexArray.hpp"
#include "openGLFunctionCallErrorManagementWrapper.hpp"
#include "BufferLayout/VertexBufferLayout.hpp"
#include "BufferLayout/LayoutElement.hpp"

VertexArray::VertexArray() {
	GL_ERROR_WRAPPER(glGenVertexArrays(1, &(this->m_vertexArrayId)));
	this->m_attribPointerId = 0;
}

VertexArray::~VertexArray() {
	GL_ERROR_WRAPPER(glDeleteVertexArrays(1, &(this->m_vertexArrayId)));
}

void VertexArray::setVertexBuffer(VertexBuffer &vbo, VertexBufferLayout &bufferLayout) {
	this->bind();
	vbo.bind();

	auto layoutElements = bufferLayout.getLayoutElements();
	unsigned int offset = 0;
	for (LayoutElement &currentElement: layoutElements) {
		GL_ERROR_WRAPPER(glVertexAttribPointer(this->m_attribPointerId,
											   currentElement.m_amount,
											   currentElement.m_type,
											   GL_FALSE,
											   bufferLayout.getStrideLength(),
											   (void*)offset));
		GL_ERROR_WRAPPER(glEnableVertexAttribArray(this->m_attribPointerId));

		this->m_attribPointerId++;
		offset += currentElement.m_amount * LayoutElement::getSizeOfType(currentElement.m_type);
	}

	vbo.unbind();
	this->unbind();
}

void VertexArray::setElementBuffer(ElementBuffer &ebo) {
	this->bind();
	ebo.bind();
	this->unbind();
	ebo.unbind();
}

void VertexArray::unsetElementBuffer() {
	this->bind();
	ElementBuffer::unbind();
	this->unbind();
}

void VertexArray::bind() {
	GL_ERROR_WRAPPER(glBindVertexArray(this->m_vertexArrayId));
}

void VertexArray::unbind() {
	GL_ERROR_WRAPPER(glBindVertexArray(0));
}
