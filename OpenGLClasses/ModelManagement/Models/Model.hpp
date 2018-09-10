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

	void rotate(glm::vec3 rotationAboutEachAxis);
	void translate(glm::vec3 translationAlongEachAxis);
	void scale(glm::vec3 scalingOnEachAxis);

	const Transformation& getModelTransformation();

	void draw(Shader &shaderProgram);

private:
	std::vector<ModelMesh *>	m_meshList;
};


#endif //LEARNINGOPENGL_MODEL_HPP
