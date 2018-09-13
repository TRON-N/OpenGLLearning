//
// Created by Leonard VAN GEND on 2018/09/04.
//

#include "VertexBufferLayout.hpp"

VertexBufferLayout::VertexBufferLayout() {
	this->m_strideLength = 0;
}

VertexBufferLayout::~VertexBufferLayout() {

}

const std::vector<LayoutElement> &VertexBufferLayout::getLayoutElements() {
	return this->m_layoutElements;
}

void VertexBufferLayout::push(unsigned int type, unsigned count, bool shouldNormalize) {
	this->m_strideLength += count * LayoutElement::getSizeOfType(type);
	this->m_layoutElements.emplace_back(type, count, shouldNormalize);
}

unsigned int VertexBufferLayout::getStrideLength() {
	return this->m_strideLength;
}

VertexBufferLayout::VertexBufferLayout(const VertexBufferLayout &obj) {
	*this = obj;
}

VertexBufferLayout &VertexBufferLayout::operator=(const VertexBufferLayout &obj) {
	if (this != &obj) {
		this->m_strideLength = obj.m_strideLength;
		this->m_layoutElements = obj.m_layoutElements;
	}
	return *this;
}
