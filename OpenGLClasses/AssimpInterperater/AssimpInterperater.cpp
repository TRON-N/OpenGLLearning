//
// Created by Leonard VAN GEND on 2018/09/06.
//

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include <cassert>
#include "AssimpInterperater.hpp"

AssimpInterperater::AssimpInterperater(std::string fileName) {
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		exit(EXIT_FAILURE);
	}
	this->m_scene = scene;
	processNode(scene->mRootNode);
}

std::vector<float> AssimpInterperater::getVertexPositions() {
	return this->m_vertexPositions;
}

std::vector<float> AssimpInterperater::getVertexTextureCoords() {
	return this->m_vertexTextureCoords;
}

std::vector<float> AssimpInterperater::getVertexNormals() {
	return this->m_vertexNormals;
}

std::vector<unsigned int> AssimpInterperater::getVertexIndices() {
	return this->m_vertexIndices;
}

void AssimpInterperater::processNode(aiNode *node) {
	assert(node != nullptr);
//	assert(node->mNumMeshes == 1);
	std::cout << "meshes in file: " << node->mNumMeshes << std::endl;
//	assert(node->mNumChildren == 0);
	std::cout << "num of childern: " << node->mNumChildren << std::endl;
	processMesh(node->mChildren[0]->mMeshes[0]);
}

void AssimpInterperater::processMesh(unsigned int meshId) {
	assert(this->m_scene != nullptr);
	aiMesh *mesh = this->m_scene->mMeshes[meshId];
	assert(mesh != nullptr);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		this->m_vertexPositions.push_back(mesh->mVertices[i].x);
		this->m_vertexPositions.push_back(mesh->mVertices[i].y);
		this->m_vertexPositions.push_back(mesh->mVertices[i].z);

		this->m_vertexNormals.push_back(mesh->mNormals[i].x);
		this->m_vertexNormals.push_back(mesh->mNormals[i].y);
		this->m_vertexNormals.push_back(mesh->mNormals[i].z);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			this->m_vertexIndices.push_back(face.mIndices[j]);
			assert(j < 3);
		}
	}
}
