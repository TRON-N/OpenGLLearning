//
// Created by Leonard on 2018/08/29.
//

#include <glad/glad.h>
#include <iostream>
#include "../Includes/VertexArray.hpp"
#include "../Includes/openGLFunctionCallErrorManagementWrapper.hpp"

VertexArray::VertexArray() {
	GL_ERROR_WRAPPER(glGenVertexArrays(1, &(this->m_vertexArrayId)));
	this->m_attribPointerId = 0;
}

VertexArray::~VertexArray() {
	GL_ERROR_WRAPPER(glDeleteVertexArrays(1, &(this->m_vertexArrayId)));
	std::cout << "VAO destructor called" << std::endl;
}

void VertexArray::setVertexBuffer(VertexBuffer &vbo, VertexBufferLayout &bufferLayout) {
	this->bind();
	vbo.bind();

	auto layoutElements = bufferLayout.getLayoutElements();
	unsigned int offset = 0;
	for (LayoutElement &currentElement: layoutElements) {
		void *ptrOffset = reinterpret_cast<void *>(offset);

		GL_ERROR_WRAPPER(glVertexAttribPointer(this->m_attribPointerId,
											   currentElement.m_amount,
											   currentElement.m_type,
											   GL_FALSE,
											   bufferLayout.getStrideLength(),
												ptrOffset));
		GL_ERROR_WRAPPER(glEnableVertexAttribArray(this->m_attribPointerId));

		this->m_attribPointerId++;
		offset += currentElement.m_amount * LayoutElement::getSizeOfType(currentElement.m_type);
	}

	vbo.unbind();
	this->unbind();
}

void VertexArray::setElementBuffer(ElementBuffer &ebo) {
	this->bind();
	ebo.setUpForVertexArray();
	this->unbind();
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

VertexArray::VertexArray(VertexArray &obj) {
	std::cout << "ERROR: VertexArray objects cannot be copied" << std::endl;
	*this = obj;
	assert(nullptr);
}

VertexArray &VertexArray::operator=(const VertexArray &obj){
	std::cout << "ERROR: VertexArray objects cannot be copied" << std::endl;
	this->m_attribPointerId = obj.m_attribPointerId;
	assert(nullptr);
	return *this;
}
