//
// Created by Leonard on 2018/09/09.
//

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Model.hpp"
#include "../../Shader.hpp"

Model::Model(std::vector<ModelMesh *> meshList) : m_meshList(meshList), m_activeAnimation(nullptr){
}

Model::~Model() {
	for (auto &mesh: this->m_meshList) {
		delete mesh;
		mesh = nullptr;
	}
	std::cout << "Model destructor called" << std::endl;
}

void Model::rotate(glm::vec3 rotationAboutEachAxis) {
	this->m_modelTransformation.m_rotation = rotationAboutEachAxis;
}

void Model::translate(glm::vec3 translationAlongEachAxis) {
	this->m_modelTransformation.m_translation = translationAlongEachAxis;
}

void Model::scale(glm::vec3 scalingOnEachAxis) {
	this->m_modelTransformation.m_scaling = scalingOnEachAxis;
}

void Model::draw(Shader &shaderProgram) {
	Transformation currentTransform = this->m_modelTransformation;

	if (this->m_activeAnimation != nullptr)
		currentTransform += this->m_activeAnimation->getCurrentTransformation();

	glm::mat4 modelToWorldMatrix = currentTransform.getTransformationMatrix();

	for (ModelMesh *mesh: this->m_meshList) {

		mesh->getVertexArray().bind();
		shaderProgram.setUniformMatrix4fv("model", glm::value_ptr(modelToWorldMatrix), GL_FALSE);
		glDrawElements(GL_TRIANGLES, mesh->getVertexAmount(), GL_UNSIGNED_INT, 0);;
	}
}

const Transformation &Model::getModelTransformation() {
	return this->m_modelTransformation;
}

void Model::addAnimation(Animation &animation, const std::string &name) {
	this->m_animationList[name] = animation;
	this->m_animationList[name].registerObserver(this);
}

void Model::startAnimation(const std::string &name) {
	if (this->m_animationList.find(name) != this->m_animationList.end()) {
		this->m_animationList[name].start();
		this->m_activeAnimation = &(this->m_animationList[name]);
		return;
	}
	std::cout << "That animation is not stored in this model" << std::endl;
}

void Model::stopAnimation() {
	this->m_activeAnimation->stop();
	this->m_activeAnimation = nullptr;
}

void Model::notify(void *arg) {
	this->m_modelTransformation += this->m_activeAnimation->getFinalTransformation();
	this->m_activeAnimation = nullptr;
}
