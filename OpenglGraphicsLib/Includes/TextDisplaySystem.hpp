//
// Created by Leonard on 2018/09/23.
//

#ifndef OPENGLLEARNING_TEXTDISPLAYSYSTEM_HPP
#define OPENGLLEARNING_TEXTDISPLAYSYSTEM_HPP


#include <glm/vec3.hpp>
#include <string>
#include <Model.hpp>
#include "s_CharacterGlyph.hpp"
#include "TextModel.hpp"

class TextDisplaySystem {
public:
	TextDisplaySystem();
	TextDisplaySystem(std::string fontFile, int fontSize);
	TextDisplaySystem(const TextDisplaySystem &obj);
	TextDisplaySystem &operator=(const TextDisplaySystem &obj);
	~TextDisplaySystem();

	TextModel *getTextModel(const std::string &text);
	void deleteTextModelMesh(const std::string &text);

	bool isTextModelMeshCreated(const std::string &text);
	Shader &getTextShader();

private:
	ModelMesh *getCharacterMesh(Texture *glyphTexture,
								glm::vec2 adjustedPosition,
								glm::vec2 size);
	void populateGlyphList(std::string fontFile, int fontSize);

	std::unordered_map<std::string, std::vector<ModelMesh *>> m_textMeshList;
	std::unordered_map<char, s_CharacterGlyph> m_glyphList;
	Shader *m_textShader;

};


#endif //OPENGLLEARNING_TEXTDISPLAYSYSTEM_HPP
