//
// Created by Leonard VAN GEND on 2018/09/06.
//

#include <assimp/postprocess.h>
#include <iostream>
#include <cassert>
#include "AssimpInterperater.hpp"

AssimpInterperater::AssimpInterperater(std::string fileName) {
	const aiScene *scene = this->m_assimpImporter.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << this->m_assimpImporter.GetErrorString() << std::endl;
		exit(EXIT_FAILURE);
	}
	this->m_scene = scene;
}

void AssimpInterperater::processAssimpNode(aiNode *node) {
	assert(node != nullptr);
	std::cout << "Meshes In Node: " << node->mNumMeshes << std::endl;
	std::cout << "Children In Node: " << node->mNumChildren << std::endl;
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		this->processAssimpNode(node->mChildren[i]);

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
		processAssimpMesh(node->mMeshes[i]);
}

void AssimpInterperater::processAssimpMesh(unsigned int meshId) {
	assert(this->m_scene != nullptr);
	aiMesh *mesh = this->m_scene->mMeshes[meshId];
	assert(mesh != nullptr);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 currentVertexPosition(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		glm::vec3 currentVertexNormal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		s_VertexData currentVertexData = {currentVertexPosition, currentVertexNormal, glm::vec2()};
		this->m_vertexData.push_back(currentVertexData);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace &face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			this->m_vertexDrawingIndices.push_back(face.mIndices[j]);
			assert(j < 3);
		}
	}

	this->m_modelMeshList.push_back(new ModelMesh(this->m_vertexData, this->m_vertexDrawingIndices));

	this->m_vertexData.clear();
	this->m_vertexDrawingIndices.clear();
}

std::vector<ModelMesh *> AssimpInterperater::getModelMeshList() {
	assert(this->m_scene != nullptr);
	aiNode *assimpRootNode = this->m_scene->mRootNode;
	assert(assimpRootNode != nullptr);
	assert(assimpRootNode->mNumChildren >= 1);

	processAssimpNode(assimpRootNode);
	return this->m_modelMeshList;
}

AssimpInterperater::~AssimpInterperater() {

}
