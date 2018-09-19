//
// Created by Leonard VAN GEND on 2018/09/05.
//

#ifndef LEARNINGOPENGL_MODELMESH_HPP
#define LEARNINGOPENGL_MODELMESH_HPP


#include <glm/mat4x4.hpp>
#include "VertexArray.hpp"
#include "s_VertexData.hpp"
#include "Transformation.hpp"
#include "Shader.hpp"
#include "Animation.hpp"
#include "Texture.hpp"

class ModelMesh {

public:
	ModelMesh(std::vector<s_VertexData> vertexData, std::vector<unsigned int> vertexDrawingIndices);
	ModelMesh();
	ModelMesh(const ModelMesh &obj);
	ModelMesh &operator=(const ModelMesh &obj);
	~ModelMesh();

	Transformation &getMeshTransformation();
	glm::mat4 getModelToWorldMatrix();
	VertexArray &getVertexArray();
	unsigned int getVertexAmount();


	void addTexture(const std::string &textureName, Texture *texture);
	std::unordered_map<std::string, Texture *>getTextureList();

private:
	void setUpVertexArray();
	void setElementBuffer();
	VertexArray									*m_vertexArray;
	VertexBuffer								*m_vertexBuffer;
	ElementBuffer								*m_elementBuffer;

	std::vector<s_VertexData>					m_vertexData;
	std::vector<unsigned int>					m_vertexDrawingIndices;
	std::unordered_map<std::string, Texture *>	m_textureList;

	Transformation								m_meshTransformation;
};


#endif //LEARNINGOPENGL_MODELMESH_HPP
