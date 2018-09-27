//
// Created by Leonard on 2018/09/23.
//

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/glad.h>
#include <iostream>
#include <GenericProgException.hpp>
#include "TextDisplaySystem.hpp"
#include "freeTypeErrorWrapper.hpp"

TextDisplaySystem::TextDisplaySystem() {
}

TextDisplaySystem::TextDisplaySystem(std::string fontFile, int fontSize) {
	this->populateGlyphList(fontFile, fontSize);

	const char *vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "layout (location = 1) in vec3 aNormal;\n"
									 "layout (location = 2) in vec2 aTextureCoord;\n"
									 "out vec2 TexCoords;\n"
									 "uniform mat4 projection;\n"
									 "uniform mat4 model;"
									 "void main()\n"
									 "{\n"
									 "	gl_Position = projection * model * vec4(aPos, 1.0);\n"
									 "	TexCoords = aTextureCoord;\n"
									 "}\0";

	const char *fragmentShaderSource = "#version 330 core\n"
									   "in vec2 TexCoords;\n"
									   "out vec4 color;\n"
									   "uniform sampler2D glyphTexture;\n"
									   "uniform vec3 textColor;\n"
									   "void main()\n"
									   "{\n"
									   "	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(glyphTexture, TexCoords).r);\n"
									   "	color = vec4(textColor, 1.0) * sampled;\n"
									   "}\0";

	this->m_textShader = new Shader(vertexShaderSource, fragmentShaderSource);
}

TextDisplaySystem::TextDisplaySystem(const TextDisplaySystem &obj) {
	std::cout << "ERROR: Texture objects cannot be copied" << std::endl;
	*this = obj;
	assert(false);
}

TextDisplaySystem &TextDisplaySystem::operator=(const TextDisplaySystem &obj) {
	std::cout << "ERROR: Texture objects cannot be copied" << std::endl;
	this->m_textMeshList = obj.m_textMeshList;
	assert(false);
	return *this;
}

TextDisplaySystem::~TextDisplaySystem() {
	for (auto characterGlyph: this->m_glyphList) {
		delete (characterGlyph.second.texture);
	}

	for (auto meshList: this->m_textMeshList) {
		for (auto mesh: meshList.second)
			delete mesh;
	}
}

TextModel *TextDisplaySystem::getTextModel(const std::string &text) {
	if (this->m_textMeshList.find(text) != this->m_textMeshList.end())
		return new TextModel(this->m_textMeshList[text]);
	float offset = 0;
	std::vector<ModelMesh *> currentTextMeshList;
	for (char character: text) {
		s_CharacterGlyph characterGlyph = this->m_glyphList[character];
		glm::vec2 scaledSize(characterGlyph.size.x, characterGlyph.size.y);

		glm::vec2 adjustedPosition;
		adjustedPosition.x = characterGlyph.bearing.x + offset;
		adjustedPosition.y = -(scaledSize.y - characterGlyph.bearing.y);

		offset += (characterGlyph.advance);

		currentTextMeshList.push_back(this->getCharacterMesh(characterGlyph.texture,
															 adjustedPosition,
															 scaledSize));
	}
	this->m_textMeshList[text] = currentTextMeshList;
	return new TextModel(currentTextMeshList);
}

ModelMesh *TextDisplaySystem::getCharacterMesh(Texture *glyphTexture, glm::vec2 adjustedPosition, glm::vec2 size) {

	s_VertexData topRightCorner;
	topRightCorner.position = {adjustedPosition.x + size.x, adjustedPosition.y + size.y, 0.0f};
	topRightCorner.textureCoordinate = {1.0f, 0.0f};
	s_VertexData topLeftCorner;
	topLeftCorner.position = {adjustedPosition.x, adjustedPosition.y + size.y, 0.0f};
	topLeftCorner.textureCoordinate = {0.0f, 0.0f};
	s_VertexData bottomRightCorner;
	bottomRightCorner.position = {adjustedPosition.x + size.x, adjustedPosition.y, 0.0f};
	bottomRightCorner.textureCoordinate = {1.0f, 1.0f};
	s_VertexData bottomLeftCorner;
	bottomLeftCorner.position = {adjustedPosition.x, adjustedPosition.y, 0.0f};
	bottomLeftCorner.textureCoordinate = {0.0f, 1.0f};

	std::vector<unsigned int> vertexDrawingOrder = {0, 1, 2, 0, 3, 2};
	std::vector<s_VertexData> vertexData = {topLeftCorner, topRightCorner, bottomRightCorner, bottomLeftCorner};

	ModelMesh *newModelMesh = new ModelMesh(vertexData, vertexDrawingOrder);
	newModelMesh->addTexture("glyphTexture", glyphTexture);

	return newModelMesh;
}

void TextDisplaySystem::populateGlyphList(std::string fontFile, int fontSize) {
	FT_Library freeTypeLib;
	FREE_TYPE_ERROR_WRAPPER(FT_Init_FreeType(&freeTypeLib));

	FT_Face face;
	if (FT_New_Face(freeTypeLib, fontFile.c_str(), 0, &face) != 0)
		throw GenericProgException("Error: Could not open font file");
	FREE_TYPE_ERROR_WRAPPER(FT_Set_Pixel_Sizes(face, 0, fontSize));

	for (int character = 0; character < 128; character++) {
		FREE_TYPE_ERROR_WRAPPER(FT_Load_Char(face, character, FT_LOAD_RENDER));

		s_CharacterGlyph newCharacterGlyph;
		newCharacterGlyph.texture = new GlyphTexture(face->glyph->bitmap.buffer, GL_RED, face->glyph->bitmap.width,
													 face->glyph->bitmap.rows);
		newCharacterGlyph.size = {face->glyph->bitmap.width, face->glyph->bitmap.rows};
		newCharacterGlyph.bearing = {face->glyph->bitmap_left, face->glyph->bitmap_top};
		newCharacterGlyph.advance = face->glyph->advance.x / 64; //Divide by 64 because it is a fixed point number;
		this->m_glyphList[character] = newCharacterGlyph;
	}
	FT_Done_Face(face);
	FT_Done_FreeType(freeTypeLib);
}

Shader &TextDisplaySystem::getTextShader() {
	return *this->m_textShader;
}

void TextDisplaySystem::deleteTextModelMesh(const std::string &text) {
	auto textMeshListIter = this->m_textMeshList.find(text);
	if (textMeshListIter == this->m_textMeshList.end()) {
		std::cout << "ERROR: Cannot delete a textMesh that does not exist" << std::endl;
		assert(false);
	}
	for (auto mesh: textMeshListIter->second)
		delete mesh;
	this->m_textMeshList.erase(textMeshListIter);
}

bool TextDisplaySystem::isTextModelMeshCreated(const std::string &text) {
	return this->m_textMeshList.find(text) != this->m_textMeshList.end();
}

