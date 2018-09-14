//
// Created by Leonard on 2018/09/14.
//

#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.hpp"

Camera::Camera(Shader *shaderProgram, float cameraViewWidth, float cameraViewHeight) {
	this->m_shaderProgram = shaderProgram;
	this->m_isAnimationActive = false;

	float halfWidth = cameraViewWidth / 2.0f;
	float halfHeight = cameraViewHeight / 2.0f;

	this->m_widthAndHeight = {cameraViewWidth, cameraViewHeight};

	glm::mat4 projection(1.0f);
	projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.1f, 100.0f);

	this->m_shaderProgram->setUniformMatrix4fv("projection", glm::value_ptr(projection));
	this->sendTransfromationMatrixToShader();
}

Camera::~Camera() {
}

Camera::Camera(const Camera &obj) {
	*this = obj;
}

Camera &Camera::operator=(const Camera &obj) {
	if (this != &obj) {
		this->m_transformation = obj.m_transformation;
		this->m_shaderProgram = obj.m_shaderProgram;
		this->m_widthAndHeight = obj.m_widthAndHeight;
		this->m_animation = obj.m_animation;
		this->m_isAnimationActive = obj.m_isAnimationActive;
	}
	return *this;
}

void Camera::translate(glm::vec3 translationAlongEachAxis) {
	this->m_transformation.m_translation = translationAlongEachAxis;
	this->m_transformation.m_translation *= -1;
	this->sendTransfromationMatrixToShader();
}

void Camera::rotate(glm::vec3 rotationAboutEachAxis) {
	this->m_transformation.m_rotation = rotationAboutEachAxis;
	this->m_transformation.m_rotation *= -1;
	this->sendTransfromationMatrixToShader();
}

void Camera::sendTransfromationMatrixToShader() {
	this->m_shaderProgram->setUniformMatrix4fv("view",
											   glm::value_ptr(this->m_transformation.getTransformationMatrix()));
}

const Transformation &Camera::getTransformation() {
	return this->m_transformation;
}

const glm::vec2 Camera::getWidthAndHeight() {
	return this->m_widthAndHeight;
}

void Camera::animatedMove(float durationInSeconds, glm::vec3 destinationTranslation, glm::vec3 destinationRotation) {
	if (this->m_isAnimationActive == false) {
		this->m_animation = Animation();
		this->m_isAnimationActive = true;

		KeyFrame startKeyFrame(0.0f, Transformation());

		Transformation endTransformation;
		endTransformation.m_rotation = destinationRotation;
		endTransformation.m_translation = destinationTranslation;
		endTransformation.m_rotation *= -1;
		endTransformation.m_translation *= -1;
		endTransformation.m_translation -= this->m_transformation.m_translation;
		endTransformation.m_rotation -= this->m_transformation.m_rotation;

		KeyFrame endKeyFrame(durationInSeconds, endTransformation);
		this->m_animation.addKeyFrame(startKeyFrame);
		this->m_animation.addKeyFrame(endKeyFrame);
		this->m_animation.registerObserver(this);
		this->m_animation.start();
	}
}

void Camera::update() {
	if (this->m_isAnimationActive) {
		Transformation newTrans = this->m_transformation + this->m_animation.getCurrentTransformation();
//		if (this->m_transformation.m_translation.x <= 0.001)
//			this->m_transformation = m_animation.getFinalTransformation();
//		this->sendTransfromationMatrixToShader();
		this->m_shaderProgram->setUniformMatrix4fv("view", glm::value_ptr(newTrans.getTransformationMatrix()));
	}
}

void Camera::notify(void *arg) {
	assert(arg == nullptr);
	this->m_transformation += this->m_animation.getFinalTransformation();
//	delete this->m_animation;
	this->m_isAnimationActive = false;
}
