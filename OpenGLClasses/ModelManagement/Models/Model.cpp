//
// Created by Leonard on 2018/09/09.
//

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Model.hpp"
#include "../../Shader.hpp"

Model::Model(std::vector<ModelMesh *> meshList) : m_meshList(meshList){
}

Model::~Model() {
	for (auto &mesh: this->m_meshList) {
		delete mesh;
		mesh = nullptr;
	}
	std::cout << "Model destructor called" << std::endl;
}

void Model::rotate(glm::vec3 rotationAboutEachAxis) {
	for (ModelMesh *mesh: this->m_meshList)
		mesh->getMeshTransformation().m_rotation = rotationAboutEachAxis;
}

void Model::translate(glm::vec3 translationAlongEachAxis) {
	for (ModelMesh *mesh: this->m_meshList)
		mesh->getMeshTransformation().m_translation = translationAlongEachAxis;
}

void Model::scale(glm::vec3 scalingOnEachAxis) {
	for (ModelMesh *mesh: this->m_meshList)
		mesh->getMeshTransformation().m_scaling = scalingOnEachAxis;
}

void Model::draw(Shader &shaderProgram) {
	for (ModelMesh *mesh: this->m_meshList) {
		mesh->getVertexArray().bind();
		shaderProgram.setUniformMatrix4fv("model", glm::value_ptr(mesh->getModelToWorldMatrix()), GL_FALSE);
		glDrawElements(GL_TRIANGLES, mesh->getVertexAmount(), GL_UNSIGNED_INT, 0);;
	}
}
