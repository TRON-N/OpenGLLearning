//
// Created by Leonard VAN GEND on 2018/09/04.
//

#include <glad/glad.h>
#include <cassert>
#include "LayoutElement.hpp"

LayoutElement::LayoutElement(unsigned int type, unsigned int ammount, bool shouldNormalize) {
	this->m_ammount = ammount;
	this->m_type = type;
	this->m_shouldNormalize = shouldNormalize ? 0 : 1;
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
