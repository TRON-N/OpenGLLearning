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
#include <assimp/Importer.hpp>

class AssimpInterperater {
public:
	AssimpInterperater(std::string fileName);
	~AssimpInterperater();
	std::vector<ModelMesh *> getModelMeshList();


private:
	void processAssimpNode(aiNode *node);
	void processAssimpMesh(unsigned int meshId);
	std::vector<s_VertexData>	m_vertexData;
	std::vector<unsigned int>	m_vertexDrawingIndices;
	std::vector<ModelMesh *>		m_modelMeshList;
	const aiScene *				m_scene;
	Assimp::Importer			m_assimpImporter;
};


#endif //LEARNINGOPENGL_ASSIMPINTERPERATER_HPP
