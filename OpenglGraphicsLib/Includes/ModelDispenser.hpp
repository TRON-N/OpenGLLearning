//
// Created by Leonard VAN GEND on 2018/09/18.
//

#ifndef LEARNINGOPENGL_MODELDISPENCER_HPP
#define LEARNINGOPENGL_MODELDISPENCER_HPP


#include <string>
#include "Model.hpp"
#include "AssimpInterpreter.hpp"

class ModelDispenser {
public:
	ModelDispenser();

	ModelDispenser(const ModelDispenser &obj);

	ModelDispenser &operator=(const ModelDispenser &obj);

	~ModelDispenser();

	Model *getModel(std::string fileName, std::string filePath);

private:
	std::unordered_map<std::string, AssimpInterpreter *> m_interpereterPerFileList;
};


#endif //LEARNINGOPENGL_MODELDISPENCER_HPP
