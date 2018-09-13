//
// Created by Leonard VAN GEND on 2018/09/05.
//

#include "Model.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <iostream>
#include "ModelMesh.hpp"

ModelMesh::ModelMesh(std::vector<s_VertexData> vertexData, std::vector<unsigned int> vertexDrawingIndices) :
		m_vertexData(vertexData), m_vertexDrawingIndices(vertexDrawingIndices){

	assert(this->m_vertexDrawingIndices.size() <= UINT_MAX);
	assert(this->m_vertexData.size() <= UINT_MAX);

	this->m_elementBuffer = nullptr;
	this->m_vertexArray = nullptr;
	this->m_vertexBuffer = nullptr;

	this->setUpVertexArray();
	this->setElementBuffer();
}

ModelMesh::~ModelMesh() {
	delete this->m_vertexBuffer;
	delete this->m_elementBuffer;
	delete this->m_vertexArray;
}

Transformation &ModelMesh::getMeshTransformation() {
	return this->m_meshTransformation;
}

glm::mat4 ModelMesh::getModelToWorldMatrix() {
	return m_meshTransformation.getTransformationMatrix();
}

VertexArray &ModelMesh::getVertexArray() {
	return *this->m_vertexArray;
}

void ModelMesh::setElementBuffer() {
	//The vertex array should be set up before this function call.
	assert(this->m_vertexArray != nullptr);

	this->m_elementBuffer = new ElementBuffer(this->m_vertexDrawingIndices.size() * sizeof(int),
			&this->m_vertexDrawingIndices[0], GL_STATIC_DRAW);
	this->m_vertexArray->setElementBuffer(*this->m_elementBuffer);
}

void ModelMesh::setUpVertexArray() {
	//The vertex array should not be set up before this function call.
	assert(this->m_vertexArray == nullptr);

	this->m_vertexBuffer = new VertexBuffer(this->m_vertexData.size() * sizeof(s_VertexData), &this->m_vertexData[0]);
	VertexBufferLayout bufferLayout;

	bufferLayout.push(GL_FLOAT, 3);
	bufferLayout.push(GL_FLOAT, 3);
	bufferLayout.push(GL_FLOAT, 2);

	this->m_vertexArray = new VertexArray;
	this->m_vertexArray->setVertexBuffer(*this->m_vertexBuffer, bufferLayout);
}

unsigned int ModelMesh::getVertexAmount() {
	return this->m_vertexDrawingIndices.size();
}

void ModelMesh::addTexture(const std::string &textureName, Texture *texture) {
	if (this->m_textureList.find(textureName) == this->m_textureList.end())
		this->m_textureList[textureName] = texture;
	else
		std::cout << "That texture is already in the list" << std::endl;
}

std::unordered_map<std::string, Texture *> ModelMesh::getTextureList() {
	return this->m_textureList;
}

ModelMesh::ModelMesh() {

}

ModelMesh::ModelMesh(const ModelMesh &obj) {
	std::cout << "ERROR: ModelMesh objects cannot be copied" << std::endl;
	assert(&obj == nullptr);
}

ModelMesh &ModelMesh::operator=(const ModelMesh &obj) {
	std::cout << "ERROR: ModelMesh objects cannot be copied" << std::endl;
	assert(&obj == nullptr);
	return *this;
}
