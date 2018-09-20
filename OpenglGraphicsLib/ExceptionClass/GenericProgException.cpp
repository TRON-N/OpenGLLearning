//
// Created by Leonard VAN GEND on 2018/08/20.
//

#include "GenericProgException.hpp"

GenericProgException::GenericProgException(const char *message) {
	this->_message = message;
}

const char *GenericProgException::what() const noexcept {
	return this->_message;
}
