//
// Created by Leonard on 2018/09/24.
//

#include "TextModel.hpp"

TextModel::TextModel(std::vector<ModelMesh *> meshList) : Model(meshList) {
}

TextModel::TextModel() : Model() {
}

void TextModel::draw(Shader &shaderProgram, glm::vec3 color) {
	shaderProgram.setUniform3f("textColor", color);
	Model::draw(shaderProgram);
}
