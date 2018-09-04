//
// Created by Leonard VAN GEND on 2018/09/04.
//

#include <glad/glad.h>
#include <cassert>
#include "LayoutElement.hpp"

LayoutElement::LayoutElement(unsigned int type, unsigned int amount, bool shouldNormalize) {
	this->m_amount = amount;
	this->m_type = type;
	this->m_shouldNormalize = shouldNormalize;
}

LayoutElement::~LayoutElement() {
}

unsigned int LayoutElement::getSizeOfType(unsigned int type) {
	switch (type) {
		case GL_FLOAT:
			return 4;
		case GL_INT:
			return 2;
		default:
			assert(false);
	}
	return 0;
}
