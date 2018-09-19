//
// Created by Leonard VAN GEND on 2018/09/07.
//

#ifndef LEARNINGOPENGL_TEXTURE_HPP
#define LEARNINGOPENGL_TEXTURE_HPP


#include <string>

class Texture {
public:
	Texture(unsigned char *data, unsigned int format, int width, int height);
	Texture();
	Texture(const Texture &obj);
	Texture &operator=(const Texture &obj);
	~Texture();

	unsigned int getId();
	void bind();
	void setActiveTextureSlot(unsigned int textureSlot);
	void activateDefaultTextureSlot();
	void unbind();

private:
	unsigned int	m_textureId;
};


#endif //LEARNINGOPENGL_TEXTURE_HPP
