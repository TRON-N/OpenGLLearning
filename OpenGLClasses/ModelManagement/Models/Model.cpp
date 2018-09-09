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

void Model::rotate(float xRotation, float yRotation, float zRotation) {
	for (ModelMesh *mesh: this->m_meshList)
		mesh->rotate(xRotation, yRotation, zRotation);
}

void Model::translate(float xTranslation, float yTranslation, float zTranslation) {
	for (ModelMesh *mesh: this->m_meshList)
		mesh->translate(xTranslation, yTranslation, zTranslation);
}

void Model::scale(float xScaleFactor, float yScaleFactor, float zScaleFactor) {
	for (ModelMesh *mesh: this->m_meshList)
		mesh->scale(xScaleFactor, yScaleFactor, zScaleFactor);
}

void Model::draw(Shader &shaderProgram) {
	for (ModelMesh *mesh: this->m_meshList) {
		mesh->getVertexArray().bind();
		shaderProgram.setUniformMatrix4fv("model", glm::value_ptr(mesh->getModelToWorldMatrix()), GL_FALSE);
		glDrawElements(GL_TRIANGLES, mesh->getVertexAmount(), GL_UNSIGNED_INT, 0);;
	}
}
