//
// Created by Leonard on 2018/09/24.
//

#ifndef OPENGLLEARNING_TEXTMODEL_HPP
#define OPENGLLEARNING_TEXTMODEL_HPP


#include <Model.hpp>

class TextModel : public Model {
public:
	TextModel(std::vector<ModelMesh *> meshList);
	TextModel();
	void draw(Shader &shaderProgram, glm::vec3 color);
};


#endif //OPENGLLEARNING_TEXTMODEL_HPP
