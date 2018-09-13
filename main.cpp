#include <SDL.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "OpenGLClasses/ModelManagement/AssimpInterperater/AssimpInterpreter.hpp"
#include "OpenGLClasses/openGLFunctionCallErrorManagementWrapper.hpp"
#include "OpenGLClasses/ModelManagement/Models/Model.hpp"

class testNotification : public i_Observer {
public:
	bool m_isActive;

	testNotification() {
		this->m_isActive = false;
	}

	void notify(void *arg) override {
		this->m_isActive = false;
	}
};

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource =	"#version 330 core\n"
									"layout (location = 0) in vec3 aPos;\n"
		 							"layout (location = 1) in vec3 aNormal;\n"
		 							"layout (location = 2) in vec2 atexCoord;\n"

									"uniform mat4 model;\n"
									"uniform mat4 view;\n"
									"uniform mat4 projection;\n"

		  							"out vec2 texCoord;\n"

									"void main()\n"
									"{\n"
									"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
		 							"	texCoord = atexCoord;\n"
									"}\0";

const char *fragmentShaderSource = 	"#version 330 core\n"
									"\n"
		 							"out vec4 FragColor;\n"
									"in vec2 texCoord;\n"
									"\n"
									"// texture sampler\n"
									"uniform sampler2D texture_diffuse1;\n"
									"uniform sampler2D texture2;\n"
									"\n"
									"void main()\n"
									"{\n"
									"	FragColor = texture(texture_diffuse1, texCoord);\n"
									"}\0";
SDL_Window* GLOBAL_SDL_WINDOW;

void createSDLWindow() {


	// SDL: initialize and configure
	// ------------------------------

	if(SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	GLOBAL_SDL_WINDOW = SDL_CreateWindow("SDL GL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			800, 600, SDL_WINDOW_OPENGL);


}

int main(int argc, char *argv[]) {
	if (argc == 0 && argv == nullptr)
		std::cout << "no args" << std::endl;

	createSDLWindow();
	SDL_GLContext gl_context = SDL_GL_CreateContext(GLOBAL_SDL_WINDOW);
	{

	if (!gladLoadGLLoader((SDL_GL_GetProcAddress))) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	AssimpInterpreter interperater("ballo2.obj", "..");
	std::vector<ModelMesh *> modelMeshList = interperater.getModelMeshList();

	Animation testAnimation;

	Transformation keyFrame1Transformation;
	KeyFrame keyFrame1(0.0f, keyFrame1Transformation);

	Transformation keyFrame2Transformation;
	keyFrame2Transformation.m_translation = glm::vec3(0.1, -0.2, 0);
//	keyFrame2Transformation.m_rotation = glm::vec3(0, 0, -10);
	keyFrame2Transformation.m_scaling = glm::vec3(1.1, 0.8, 1.1);
	KeyFrame keyFrame2(0.10f, keyFrame2Transformation);

	Transformation keyFrame3Transformation;
	keyFrame3Transformation.m_translation = glm::vec3(0.15, 0.4, 0);
//	keyFrame3Transformation.m_rotation = glm::vec3(0, 0, -10);
	keyFrame3Transformation.m_scaling = glm::vec3(0.9, 1.2, 0.9);
	KeyFrame keyFrame3(0.17f, keyFrame3Transformation);

	Transformation keyFrame4Transformation;
	keyFrame4Transformation.m_translation = glm::vec3(0.2, 1.5, 0);
//	keyFrame4Transformation.m_rotation = glm::vec3(0, 0, -20);
	KeyFrame keyFrame4(0.25f, keyFrame4Transformation);

	Transformation keyFrame5Transformation;
	keyFrame5Transformation.m_translation = glm::vec3(0.4, -0.2, 0);
//	keyFrame4Transformation.m_rotation = glm::vec3(0, 0, -20);
	keyFrame5Transformation.m_scaling = glm::vec3(1.1, 0.8, 1.1);
	KeyFrame keyFrame5(0.35f, keyFrame5Transformation);

	Transformation keyFrame6Transformation;
	keyFrame6Transformation.m_translation = glm::vec3(0.4, 0, 0);
	KeyFrame keyFrame6(0.40f, keyFrame6Transformation);


	testAnimation.addKeyFrame(keyFrame1);
	testAnimation.addKeyFrame(keyFrame2);
	testAnimation.addKeyFrame(keyFrame3);
	testAnimation.addKeyFrame(keyFrame4);
	testAnimation.addKeyFrame(keyFrame5);
	testAnimation.addKeyFrame(keyFrame6);

	std::vector<Model *> modelList;
	std::vector<testNotification *> notificationClassList;
	std::string animationName = "testAnime";
		for (int i = 0; i < 10; i++) {
		modelList.emplace_back(new Model(modelMeshList));
		modelList.back()->addAnimation(testAnimation, animationName);
		notificationClassList.push_back(new testNotification());
		modelList.back()->registerObserver(notificationClassList.back());
	}

	glm::mat4 view(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 20.0f, -15.0f));
		view = glm::rotate(view, glm::radians(45.0f), glm::vec3(1, 0, 0));

	glm::mat4 projection(1.0f);
		projection = glm::ortho(0.0f, 30.0f, 0.0f, 30.0f, -10.0f, 100.0f);

	for (unsigned int i = 0; i < modelList.size(); i++) {
		Model *testModel = modelList[i];
		testModel->scale(glm::vec3(1.0f, 1.0f, 1.0f));
		testModel->translate(glm::vec3(6.0f + (float) i, 0.0f, -3.5f + (float) i * 3));
	}

	Shader *shaderProgram = new Shader(vertexShaderSource, fragmentShaderSource);
	shaderProgram->bind();
	shaderProgram->setUniformMatrix4fv("view", glm::value_ptr(view), GL_FALSE);
	shaderProgram->setUniformMatrix4fv("projection", glm::value_ptr(projection), GL_FALSE);

	glEnable(GL_DEPTH_TEST);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
//	testModel.startAnimation("testAnime");

		AssimpInterpreter interpreter2("cubo.obj", "..");
		std::vector<ModelMesh *> boxList = interpreter2.getModelMeshList();
		Model boxModel(boxList);
		boxModel.scale(glm::vec3(10, 1, 15));
		boxModel.translate(glm::vec3(15, -1.5, 10));

	bool loop = true;
	while (loop) {

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				loop = false;
				break;
			}
		}

		GL_ERROR_WRAPPER(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GL_ERROR_WRAPPER(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

//		float angle = 20.0f * 2;
//		testModel.rotate(glm::vec3(0, SDL_GetTicks() / angle, 0));

		boxModel.draw(*shaderProgram);
		for (unsigned int i = 0; i < modelList.size(); i++) {
			Model *currentModel = modelList[i];
			testNotification *currentNotificationClass = notificationClassList[i];
			currentModel->draw(*shaderProgram);

			if (currentModel->getModelTransformation().m_translation.x > 24)
				currentModel->translate(glm::vec3(6.0f, 0.0f, -3.5 + (float) i * 3));
			if (currentNotificationClass->m_isActive == false) {
				currentModel->startAnimation(animationName);
				currentNotificationClass->m_isActive = true;
			}
		}

		SDL_GL_SwapWindow(GLOBAL_SDL_WINDOW);
	}
	for (Model *model: modelList) {
		delete model;
	}

	for (testNotification *testNotificationClass: notificationClassList) {
		delete testNotificationClass;
	}

	for (ModelMesh *mesh: modelMeshList)
		delete mesh;
	delete shaderProgram;
}
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(GLOBAL_SDL_WINDOW);
	SDL_Quit();
	std::cout << "Program Ended" << std::endl;
	return 0;
}