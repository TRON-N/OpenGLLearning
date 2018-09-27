//
// Created by Leonard VAN GEND on 2018/08/20.
//

#ifndef UNTITLED_GENERICEXCEPTION_HPP
#define UNTITLED_GENERICEXCEPTION_HPP

#include <exception>
#include <string>

class GenericProgException : public std::runtime_error {
public:
	explicit GenericProgException(const std::string &message);
};


#endif //UNTITLED_GENERICEXCEPTION_HPP
