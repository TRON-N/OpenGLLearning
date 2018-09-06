//
// Created by Leonard VAN GEND on 2018/09/06.
//

#ifndef LEARNINGOPENGL_ASSIMPINTERPERATER_HPP
#define LEARNINGOPENGL_ASSIMPINTERPERATER_HPP


#include <string>
#include <vector>
#include <assimp/scene.h>

class AssimpInterperater {
public:
	AssimpInterperater(std::string fileName);
	std::vector<float>	getVertexPositions();
	std::vector<float>	getVertexTextureCoords();
	std::vector<float>	getVertexNormals();
	std::vector<unsigned int> getVertexIndices();

private:
	void processNode(aiNode *node);
	void processMesh(unsigned int meshId);
	std::vector<float>			m_vertexPositions;
	std::vector<float>			m_vertexTextureCoords;
	std::vector<float>			m_vertexNormals;
	std::vector<unsigned int>	m_vertexIndices;
	const aiScene *				m_scene;
};


#endif //LEARNINGOPENGL_ASSIMPINTERPERATER_HPP
