//
// Created by Leonard VAN GEND on 2018/09/06.
//

#include <assimp/postprocess.h>
#include <iostream>
#include <cassert>
#include <stb_image.h>
#include <glad/glad.h>
#include <GenericProgException.hpp>
#include "../../../Includes/AssimpInterpreter.hpp"

AssimpInterpreter::AssimpInterpreter(std::string fileName, std::string folderPath) {
	std::string fullFilePath = folderPath + "/" + fileName;

	const aiScene *scene = this->m_assimpImporter.ReadFile(fullFilePath, aiProcess_Triangulate
			| aiProcess_FlipUVs | aiProcess_OptimizeMeshes);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::string errorStr = "Exception: ASSIMP: ";
		errorStr.append(this->m_assimpImporter.GetErrorString());
		throw GenericProgException(errorStr.c_str());
	}
	this->m_scene = scene;
	this->m_folderPath = folderPath;
	this->m_isFileProcessed = false;
}

void AssimpInterpreter::processAssimpNode(aiNode *node) {
	assert(node != nullptr);
	std::cout << "Meshes In Node: " << node->mNumMeshes << std::endl;
	std::cout << "Children In Node: " << node->mNumChildren << std::endl;
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		this->processAssimpNode(node->mChildren[i]);

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
		processAssimpMesh(node->mMeshes[i]);
}

void AssimpInterpreter::processAssimpMesh(unsigned int meshId) {
	assert(this->m_scene != nullptr);
	aiMesh *mesh = this->m_scene->mMeshes[meshId];
	assert(mesh != nullptr);
	std::cout << "Number of texture coordinate channels: " << mesh->GetNumUVChannels() << std::endl;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 currentVertexPosition(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		glm::vec3 currentVertexNormal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		glm::vec2 currentTextureCoords;

		if (mesh->HasTextureCoords(0))
			currentTextureCoords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};

		s_VertexData currentVertexData = {currentVertexPosition, currentVertexNormal, currentTextureCoords};
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
	this->processTextures(this->m_modelMeshList.back(), this->m_scene->mMaterials[mesh->mMaterialIndex],
						  aiTextureType_DIFFUSE);

	this->m_vertexData.clear();
	this->m_vertexDrawingIndices.clear();
}

std::vector<ModelMesh *> AssimpInterpreter::getModelMeshList() {
	assert(this->m_scene != nullptr);
	aiNode *assimpRootNode = this->m_scene->mRootNode;
	assert(assimpRootNode != nullptr);
	assert(assimpRootNode->mNumChildren >= 1);

	if (this->m_isFileProcessed == false) {
		processAssimpNode(assimpRootNode);
		this->m_isFileProcessed = true;
	}
	return this->m_modelMeshList;
}

AssimpInterpreter::~AssimpInterpreter() {
	for (auto iter: this->m_textureList)
		delete iter.second;
	for (ModelMesh *mesh: this->m_modelMeshList)
		delete mesh;
}

void AssimpInterpreter::processTextures(ModelMesh *modelMesh, aiMaterial *meshMaterial, aiTextureType textureType) {

	std::string textureTypeStr;

	switch (textureType) {
		case aiTextureType_DIFFUSE:
			textureTypeStr = "texture_diffuse";
			break;
		default:
			break;
	}

	std::cout << "There are " << meshMaterial->GetTextureCount(textureType) << " textures of type: " << textureTypeStr
																			<< " in this mesh."		 << std::endl;

	int textureTypeNumber = 1;
	for (unsigned int i = 0; i < meshMaterial->GetTextureCount(textureType); i++) {
		aiString name;
		meshMaterial->GetTexture(textureType, i, &name);
		std::string textureNameStr(name.C_Str());

		if (this->m_textureList.find(textureNameStr) == this->m_textureList.end())
			this->m_textureList[textureNameStr] = this->getTextureFromFile(textureNameStr);
		std::cout << "Texture name: " << textureNameStr << std::endl;
		modelMesh->addTexture(textureTypeStr + std::to_string(textureTypeNumber),
							  this->m_textureList[textureNameStr]);
	}
}

Texture *AssimpInterpreter::getTextureFromFile(std::string fileName) {
	int width;
	int height;
	int numberOfComponents;

	std::string fullFilePath = this->m_folderPath + "/" + fileName;
	unsigned char *data = stbi_load(fullFilePath.c_str(), &width, &height, &numberOfComponents, 0);
	Texture *newTexture = nullptr;

	std::cout << "Trying to load this texture: " << fullFilePath << std::endl;

	if (data != nullptr) {

		GLenum format = GL_RGB;
		switch (numberOfComponents) {
			case 1:
				format = GL_RED;
				break;
			case 4:
				format = GL_RGBA;
				break;
			case 3:
				break;
			default:
				std::cout << "The system does not know how to interpret the file's colour format" << std::endl;
		}
		newTexture = new Texture(data, format, width, height);
	}
	stbi_image_free(data);
	if (newTexture == nullptr) {
		std::string errorStr = "Texture at " + fullFilePath + " could not be loaded.\n";
		throw GenericProgException(errorStr.c_str());
	}
	return newTexture;
}

AssimpInterpreter::AssimpInterpreter() {

}

AssimpInterpreter::AssimpInterpreter(const AssimpInterpreter &obj) {
	std::cout << "ERROR: AssimpInterpreter objects cannot be copied" << std::endl;
	*this = obj;
	assert(false);
}

AssimpInterpreter &AssimpInterpreter::operator=(const AssimpInterpreter &obj) {
	std::cout << "ERROR: AssimpInterpreter objects cannot be copied" << std::endl;
	this->m_folderPath = obj.m_folderPath;
	assert(false);
	return *this;
}
