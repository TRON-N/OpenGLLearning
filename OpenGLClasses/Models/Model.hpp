//
// Created by Leonard VAN GEND on 2018/09/05.
//

#ifndef LEARNINGOPENGL_MODEL_HPP
#define LEARNINGOPENGL_MODEL_HPP


#include <glm/mat4x4.hpp>
#include "../VertexArray.hpp"

class Model {
public:
	Model();
	~Model();

	void rotate(float xRotation, float yRotation, float zRotation);
	void scale(float scaleFactor, float yScaleFactor, float zScaleFactor);
	void translate(float xTranslation, float yTranslation, float zTranslation);

	glm::mat4 getModelToWorldMatrix();
	VertexArray & getVertexArray();

	void addVertexData(float *data, unsigned int dataType, unsigned int dataSize, unsigned int unitsPerVertex,
						   bool shouldNormalize = false);
	void setElementBuffer(unsigned int *data, unsigned int dataSize, int drawOption);

private:
	VertexArray					m_vertexArray;
	ElementBuffer				*m_elementBuffer;
	std::vector<VertexBuffer *>	m_vertexDataBuffers;

	glm::mat4					m_rotationMatrix;
	glm::mat4					m_translationMatrix;
	glm::mat4					m_scalingMatrix;
	glm::mat4					m_modelToWorldMatrix;

};


#endif //LEARNINGOPENGL_MODEL_HPP
