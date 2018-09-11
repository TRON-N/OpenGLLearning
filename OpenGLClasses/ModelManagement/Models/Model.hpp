//
// Created by Leonard on 2018/09/09.
//

#ifndef LEARNINGOPENGL_MODEL_HPP
#define LEARNINGOPENGL_MODEL_HPP

#include "ModelMesh.hpp"
#include "../../Shader.hpp"
#include "../Animation/Animation.hpp"


class Model : public i_Observer {
public:
	Model(std::vector<ModelMesh *> meshList);
	~Model();

	void rotate(glm::vec3 rotationAboutEachAxis);
	void translate(glm::vec3 translationAlongEachAxis);
	void scale(glm::vec3 scalingOnEachAxis);

	const Transformation& getModelTransformation();

	void draw(Shader &shaderProgram);

	void addAnimation(Animation &animation, const std::string &name);
	void startAnimation(const std::string &name);
	void stopAnimation();

	void notify(void *arg) override;

private:
	std::vector<ModelMesh *>					m_meshList;
	Transformation								m_modelTransformation;
	std::unordered_map<std::string, Animation>	m_animationList;
	Animation *									m_activeAnimation;
};


#endif //LEARNINGOPENGL_MODEL_HPP
