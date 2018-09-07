//
// Created by Leonard VAN GEND on 2018/09/07.
//

#ifndef LEARNINGOPENGL_TEXTURE_HPP
#define LEARNINGOPENGL_TEXTURE_HPP


#include <string>

class Texture {
	Texture(std::string path);
	~Texture();

	void bind();
	void unbind();
};


#endif //LEARNINGOPENGL_TEXTURE_HPP
