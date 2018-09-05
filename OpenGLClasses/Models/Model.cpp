//
// Created by Leonard VAN GEND on 2018/09/05.
//

#include <glm/ext/matrix_transform.hpp>
#include "Model.hpp"

Model::Model() {
	this->m_elementBuffer = nullptr;
	this->m_translationMatrix = glm::mat4(1.0f);
	this->m_rotationMatrix = glm::mat4(1.0f);
	this->m_scalingMatrix = glm::mat4(1.0f);
}

Model::~Model() {
	for (auto buffer: this->m_vertexDataBuffers)
		delete buffer;
	delete this->m_elementBuffer;
}

void Model::rotate(float xRotation, float yRotation, float zRotation) {
	glm::mat4 xRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(xRotation), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 yRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(yRotation), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 zRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(zRotation), glm::vec3(0.0f, 0.0f, 1.0f));

	this->m_rotationMatrix = glm::mat4(1.0f);
	this->m_rotationMatrix *= zRotationMatrix;
	this->m_rotationMatrix *= yRotationMatrix;
	this->m_rotationMatrix *= xRotationMatrix;
}

void Model::scale(float xScaleFactor, float yScaleFactor, float zScaleFactor) {
	this->m_scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(xScaleFactor, yScaleFactor, zScaleFactor));
}

void Model::translate(float xTranslation, float yTranslation, float zTranslation) {
	this->m_translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(xTranslation, yTranslation, zTranslation));
}

glm::mat4 Model::getModelToWorldMatrix() {
	glm::mat4 modelToWorldMatrix = glm::mat4(1.0f);
	modelToWorldMatrix *= this->m_translationMatrix;
	modelToWorldMatrix *= this->m_rotationMatrix;
	modelToWorldMatrix *= this->m_scalingMatrix;
	return modelToWorldMatrix;
}

VertexArray &Model::getVertexArray() {
	return this->m_vertexArray;
}

void Model::addVertexData(float *data, unsigned int dataType, unsigned int dataSize, unsigned int unitsPerVertex,
						  bool shouldNormalize) {
	VertexBuffer *newBuffer = new VertexBuffer(dataSize, data);
	VertexBufferLayout newLayout;
	newLayout.push(dataType, unitsPerVertex, shouldNormalize);

	this->m_vertexArray.setVertexBuffer(*newBuffer, newLayout);
	this->m_vertexDataBuffers.push_back(newBuffer);
}

void Model::setElementBuffer(unsigned int *data, unsigned int dataSize, int drawOption) {
	delete this->m_elementBuffer;
	this->m_elementBuffer = new ElementBuffer(dataSize, data, drawOption);

	this->m_vertexArray.setElementBuffer(*this->m_elementBuffer);
}
