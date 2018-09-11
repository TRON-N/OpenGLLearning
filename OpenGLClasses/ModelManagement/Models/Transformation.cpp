//
// Created by Leonard VAN GEND on 2018/09/10.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Transformation.hpp"

Transformation::Transformation() : m_translation(0.0f), m_rotation(0.0f),  m_scaling(1.0f){
}

Transformation::~Transformation() {
}

glm::mat4 Transformation::getTransformationMatrix() const{
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

glm::vec3 Transformation::getInterpolatedVec3(glm::vec3 startVector, glm::vec3 endVector,
											  float interpolationValue) {
	glm::vec3 difference(endVector.x - startVector.x, endVector.y - startVector.y, endVector.z - startVector.z);

	glm::vec3 increase(difference.x * interpolationValue, difference.y * interpolationValue,
					   difference.z * interpolationValue);

	glm::vec3 newVector(startVector);
	newVector += increase;
	return newVector;
}

Transformation Transformation::getInterpolatedTransformation(const Transformation &t1, const Transformation &t2,
															 float interpolationValue) {
	Transformation interpolatedTransformation;

	interpolatedTransformation.m_scaling = getInterpolatedVec3(t1.m_scaling, t2.m_scaling, interpolationValue);
//	No rotation Interpolation at this time
//	interpolatedTransformation.m_rotation = getInterpolatedVec3(t1.m_rotation, t2.m_rotation, interpolationValue);
	interpolatedTransformation.m_translation = getInterpolatedVec3(t1.m_translation,
																	t2.m_translation, interpolationValue);
	return interpolatedTransformation;
}

Transformation Transformation::operator +(const Transformation &rhs) const {

	Transformation newTransformation;

	newTransformation.m_translation = this->m_translation;
	newTransformation.m_translation += rhs.m_translation;

	newTransformation.m_rotation = this->m_rotation;
	newTransformation.m_rotation += rhs.m_rotation;

	newTransformation.m_scaling = this->m_scaling;
	newTransformation.m_scaling *= rhs.m_scaling;

	return newTransformation;
}

Transformation Transformation::operator +=(const Transformation &rhs) {
	this->m_translation += rhs.m_translation;
	this->m_rotation += rhs.m_rotation;
	this->m_scaling *= rhs.m_scaling;
	return *this;
}
