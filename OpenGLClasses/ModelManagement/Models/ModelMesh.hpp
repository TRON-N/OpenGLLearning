//
// Created by Leonard VAN GEND on 2018/09/05.
//

#ifndef LEARNINGOPENGL_MODELMESH_HPP
#define LEARNINGOPENGL_MODELMESH_HPP


#include <glm/mat4x4.hpp>
#include "../../VertexArray.hpp"
#include "../s_VertexData.hpp"

class ModelMesh {
public:
	ModelMesh(std::vector<s_VertexData> vertexData, std::vector<unsigned int> vertexDrawingIndices);
	~ModelMesh();

	void rotate(float xRotation, float yRotation, float zRotation);
	void scale(float scaleFactor, float yScaleFactor, float zScaleFactor);
	void translate(float xTranslation, float yTranslation, float zTranslation);

	glm::mat4 getModelToWorldMatrix();
	VertexArray & getVertexArray();

	unsigned int getVertexAmount();



private:
	void setUpVertexArray();
	void setElementBuffer();
	VertexArray					*m_vertexArray;
	VertexBuffer				*m_vertexBuffer;
	ElementBuffer				*m_elementBuffer;
	
	std::vector<s_VertexData>	m_vertexData;
	std::vector<unsigned int>	m_vertexDrawingIndices;

	glm::mat4					m_rotationMatrix;
	glm::mat4					m_translationMatrix;
	glm::mat4					m_scalingMatrix;
	glm::mat4					m_modelToWorldMatrix;

};


#endif //LEARNINGOPENGL_MODELMESH_HPP