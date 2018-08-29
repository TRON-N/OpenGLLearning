//
// Created by Leonard on 2018/08/29.
//
#include <glad/glad.h>
#include <iostream>

void clearGLErrors() {
	while (glGetError());
}

int checkForGLErrors() {
	GLenum error;
	int errorCount = 0;

	while ((error = glGetError())) {
		switch (error){
			case GL_INVALID_ENUM:
				std::cout << "OpenGL Error: An invalid enum was found" << std::endl;
				break;
			case GL_INVALID_VALUE:
				std::cout << "OpenGL Error: An invalid value was found" << std::endl;
				break;
			case GL_INVALID_OPERATION:
				std::cout << "OpenGL Error: An invalid operation was found" << std::endl;
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				std::cout << "OpenGL Error: An invalid value framebuffer operation found" << std::endl;
				break;
			case GL_OUT_OF_MEMORY:
				std::cout << "OpenGL Error: OpenGL ran out of memory" << std::endl;
				break;
			default:
				std::cout << "OpenGL Error: Unknown error occurred the application might not function correctly"
				 << std::endl;
		}
		errorCount++;
	}
	return errorCount;
};

