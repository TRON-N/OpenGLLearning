//
// Created by Leonard VAN GEND on 2018/09/18.
//

#include <iostream>
#include "ModelDispenser.hpp"

ModelDispenser::ModelDispenser() {
}

ModelDispenser::ModelDispenser(const ModelDispenser &obj) {
	std::cout << "ERROR: AssimpInterpreter objects cannot be copied" << std::endl;
	assert(&obj == nullptr);
}

ModelDispenser &ModelDispenser::operator=(const ModelDispenser &obj) {
	std::cout << "ERROR: AssimpInterpreter objects cannot be copied" << std::endl;
	assert(&obj == nullptr);
	return *this;
}

ModelDispenser::~ModelDispenser() {
	for (auto iter: this->m_interpereterPerFileList)
		delete iter.second;
}

Model *ModelDispenser::getModel(std::string fileName, std::string filePath) {
	if (this->m_interpereterPerFileList.find(fileName) == this->m_interpereterPerFileList.end())
		this->m_interpereterPerFileList[fileName] = new AssimpInterpreter(fileName, filePath);
	return new Model(this->m_interpereterPerFileList[fileName]->getModelMeshList());
}