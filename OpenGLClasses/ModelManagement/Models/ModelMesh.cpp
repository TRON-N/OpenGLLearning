//
// Created by Leonard VAN GEND on 2018/09/05.
//

#include <glm/ext/matrix_transform.hpp>
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

	this->m_translationMatrix = glm::mat4(1.0f);
	this->m_rotationMatrix = glm::mat4(1.0f);
	this->m_scalingMatrix = glm::mat4(1.0f);
}

ModelMesh::~ModelMesh() {
	delete this->m_vertexBuffer;
	delete this->m_elementBuffer;
	delete this->m_vertexArray;
}

void ModelMesh::rotate(float xRotation, float yRotation, float zRotation) {
	glm::mat4 xRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(xRotation), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 yRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(yRotation), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 zRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(zRotation), glm::vec3(0.0f, 0.0f, 1.0f));

	this->m_rotationMatrix = glm::mat4(1.0f);
	this->m_rotationMatrix *= zRotationMatrix;
	this->m_rotationMatrix *= yRotationMatrix;
	this->m_rotationMatrix *= xRotationMatrix;
}

void ModelMesh::scale(float xScaleFactor, float yScaleFactor, float zScaleFactor) {
	this->m_scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(xScaleFactor, yScaleFactor, zScaleFactor));
}

void ModelMesh::translate(float xTranslation, float yTranslation, float zTranslation) {
	this->m_translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(xTranslation, yTranslation, zTranslation));
}

glm::mat4 ModelMesh::getModelToWorldMatrix() {
	glm::mat4 modelToWorldMatrix = glm::mat4(1.0f);
	modelToWorldMatrix *= this->m_translationMatrix;
	modelToWorldMatrix *= this->m_rotationMatrix;
	modelToWorldMatrix *= this->m_scalingMatrix;
	return modelToWorldMatrix;
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
