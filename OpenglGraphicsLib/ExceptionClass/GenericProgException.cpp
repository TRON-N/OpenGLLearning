//
// Created by Leonard VAN GEND on 2018/08/20.
//

#include "GenericProgException.hpp"

GenericProgException::GenericProgException(const std::string &message) : std::runtime_error(message) {
}
