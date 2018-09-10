//
// Created by Leonard VAN GEND on 2018/09/10.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Transformation.hpp"

Transformation::Transformation() : m_rotation(0.0f), m_translation(0.0f), m_scaling(1.0f){
}

Transformation::~Transformation() {
}

glm::mat4 Transformation::getTransformationMatrix() {
	glm::mat4 modelToWorldMatrix = glm::mat4(1.0f);
	modelToWorldMatrix *= glm::translate(glm::mat4(1.0f), this->m_translation);

	glm::mat4 xRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(this->m_rotation.x), glm::vec3(1, 0, 0));
	glm::mat4 yRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(this->m_rotation.y), glm::vec3(0, 1, 0));
	glm::mat4 zRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(this->m_rotation.z), glm::vec3(0, 0, 1));

	glm::mat4 rotationMatrix(1.0f);
	rotationMatrix *= zRotationMatrix;
	rotationMatrix *= yRotationMatrix;
	rotationMatrix *= xRotationMatrix;
	modelToWorldMatrix *= rotationMatrix;

	modelToWorldMatrix *=  glm::scale(glm::mat4(1.0f), this->m_scaling);
	return modelToWorldMatrix;
}

Transformation::Transformation(const Transformation &obj) {
	*this = obj;
}

Transformation &Transformation::operator=(const Transformation &obj) {
	if (this != &obj) {
		this->m_scaling = obj.m_scaling;
		this->m_rotation = obj.m_rotation;
		this->m_translation = obj.m_translation;
	}
	return *this;
}
