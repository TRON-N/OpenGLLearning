//
// Created by Leonard VAN GEND on 2018/08/20.
//

#ifndef UNTITLED_GENERICEXCEPTION_HPP
#define UNTITLED_GENERICEXCEPTION_HPP

#include <exception>
#include <string>

class GenericProgException : public std::exception {
public:
	explicit GenericProgException(const char *message);

	GenericProgException() = default;

	GenericProgException(const GenericProgException &obj) = default;

	GenericProgException &operator=(const GenericProgException &obj) = default;

	const char *what() const noexcept override;

private:
	const char *_message;
};


#endif //UNTITLED_GENERICEXCEPTION_HPP
