//
// Created by Leonard on 2018/09/09.
//

#ifndef LEARNINGOPENGL_MODEL_HPP
#define LEARNINGOPENGL_MODEL_HPP

#include "ModelMesh.hpp"
#include "../../Shader.hpp"


class Model {
public:
	Model(std::vector<ModelMesh *> meshList);
	~Model();

	void rotate(float xRotation, float yRotation, float zRotation);
	void translate(float xTranslation, float yTranslation, float zTranslation);
	void scale(float xScaleFactor, float yScaleFactor, float zScaleFactor);

	void draw(Shader &shaderProgram);

private:
	std::vector<ModelMesh *>	m_meshList;
};


#endif //LEARNINGOPENGL_MODEL_HPP
