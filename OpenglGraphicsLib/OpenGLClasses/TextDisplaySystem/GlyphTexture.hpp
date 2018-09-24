//
// Created by Leonard on 2018/09/23.
//

#ifndef OPENGLLEARNING_GLYPHTEXTURE_HPP
#define OPENGLLEARNING_GLYPHTEXTURE_HPP


#include <Texture.hpp>

class GlyphTexture : public Texture {
public:
	GlyphTexture(unsigned char *data, unsigned int format, int width, int height);
};


#endif //OPENGLLEARNING_GLYPHTEXTURE_HPP
