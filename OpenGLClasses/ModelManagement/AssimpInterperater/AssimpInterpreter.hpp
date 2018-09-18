//
// Created by Leonard VAN GEND on 2018/09/06.
//

#ifndef LEARNINGOPENGL_ASSIMPINTERPERATER_HPP
#define LEARNINGOPENGL_ASSIMPINTERPERATER_HPP


#include <string>
#include <vector>
#include <assimp/scene.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "../Models/ModelMesh.hpp"
#include "../s_VertexData.hpp"
#include "../Texture.hpp"
#include <assimp/Importer.hpp>
#include <map>

class AssimpInterpreter {
public:
	AssimpInterpreter(std::string fileName, std::string folderPath);
	AssimpInterpreter();
	AssimpInterpreter(const AssimpInterpreter& obj);
	AssimpInterpreter &operator=(const AssimpInterpreter& obj);
	~AssimpInterpreter();
	std::vector<ModelMesh *> getModelMeshList();

private:
	void processAssimpNode(aiNode *node);
	void processAssimpMesh(unsigned int meshId);
	void processTextures(ModelMesh *modelMesh, aiMaterial *meshMaterial, aiTextureType textureType);
	Texture *getTextureFromFile(std::string fileName);

	std::vector<s_VertexData>			m_vertexData;
	std::vector<unsigned int>			m_vertexDrawingIndices;
	std::vector<ModelMesh *>			m_modelMeshList;
	std::map<std::string, Texture *>	m_textureList;
	const aiScene *						m_scene;
	Assimp::Importer					m_assimpImporter;

	std::string							m_folderPath;
	bool m_isFileProcessed;
};


#endif //LEARNINGOPENGL_ASSIMPINTERPERATER_HPP
