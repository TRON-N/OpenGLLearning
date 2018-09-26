//
// Created by Leonard on 2018/09/23.
//

#ifndef OPENGLLEARNING_S_CHARACTERGLYPH_HPP
#define OPENGLLEARNING_S_CHARACTERGLYPH_HPP

#include "GlyphTexture.hpp"

struct s_CharacterGlyph {
	GlyphTexture *texture;
	glm::ivec2 size;
	glm::ivec2 bearing;
	int advance;
};

#endif //OPENGLLEARNING_S_CHARACTERGLYPH_HPP
