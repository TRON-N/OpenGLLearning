//
// Created by Leonard on 2018/09/09.
//

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Model.hpp"

Model::Model(std::vector<ModelMesh *> meshList) : m_meshList(meshList), m_activeAnimation(nullptr){
}

Model::~Model() {
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
		currentTransform = this->m_modelTransformation + this->m_activeAnimation->getCurrentTransformation();
	glm::mat4 modelToWorldMatrix = currentTransform.getTransformationMatrix();
	shaderProgram.setUniformMatrix4fv("model", glm::value_ptr(modelToWorldMatrix), GL_FALSE);

	for (ModelMesh *mesh: this->m_meshList) {
		sendTexturesToShader(mesh, shaderProgram);
		mesh->getVertexArray().bind();
		glDrawElements(GL_TRIANGLES, mesh->getVertexAmount(), GL_UNSIGNED_INT, nullptr);;
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
	assert(arg == nullptr);
	this->m_modelTransformation += this->m_activeAnimation->getFinalTransformation();
	this->m_activeAnimation = nullptr;
	this->notifyObservers();
}

void Model::notifyObservers() {
	for (i_Observer *observer: this->m_observerList)
		observer->notify(nullptr);
}

void Model::sendTexturesToShader(ModelMesh *currentMesh, Shader &shader) {
	std::unordered_map<std::string, Texture *> textureList = currentMesh->getTextureList();

	unsigned int textureNumber = 0;
	for (auto textureIter: textureList) {
		const std::string uniformName = textureIter.first;
		Texture *texture = textureIter.second;

		texture->setActiveTextureSlot(textureNumber);
		texture->bind();
		shader.setUniformInt(uniformName, textureNumber);
		textureNumber++;
	}
}

Model::Model() {
}

Model::Model(const Model &obj) {
	*this = obj;
}

Model &Model::operator=(const Model &obj) {
	if (this != &obj) {
		this->m_meshList = obj.m_meshList;
		this->m_activeAnimation = obj.m_activeAnimation;
		this->m_animationList = obj.m_animationList;
		this->m_modelTransformation = obj.m_modelTransformation;
		this->m_observerList = obj.m_observerList;
	}
	return *this;
}

