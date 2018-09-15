#include <SDL.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "OpenGLClasses/ModelManagement/AssimpInterperater/AssimpInterpreter.hpp"
#include "OpenGLClasses/openGLFunctionCallErrorManagementWrapper.hpp"
#include "OpenGLClasses/ModelManagement/Models/Model.hpp"
#include "OpenGLClasses/Camera.hpp"

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
		keyFrame2Transformation.m_scaling = glm::vec3(1.2, 0.6, 1.2);
	KeyFrame keyFrame2(0.10f, keyFrame2Transformation);

	Transformation keyFrame3Transformation;
		keyFrame3Transformation.m_translation = glm::vec3(0.15, 0.7, 0);
//	keyFrame3Transformation.m_rotation = glm::vec3(0, 0, -10);
		keyFrame3Transformation.m_scaling = glm::vec3(0.8, 1.4, 0.8);
		KeyFrame keyFrame3(0.20f, keyFrame3Transformation);

	Transformation keyFrame4Transformation;
	keyFrame4Transformation.m_translation = glm::vec3(0.2, 1.5, 0);
//	keyFrame4Transformation.m_rotation = glm::vec3(0, 0, -20);
	KeyFrame keyFrame4(0.25f, keyFrame4Transformation);

	Transformation keyFrame5Transformation;
	keyFrame5Transformation.m_translation = glm::vec3(0.4, -0.2, 0);
//	keyFrame4Transformation.m_rotation = glm::vec3(0, 0, -20);
		keyFrame5Transformation.m_scaling = glm::vec3(1.2, 0.6, 1.2);
	KeyFrame keyFrame5(0.35f, keyFrame5Transformation);

	Transformation keyFrame6Transformation;
	keyFrame6Transformation.m_translation = glm::vec3(0.4, 0, 0);
		KeyFrame keyFrame6(0.37f, keyFrame6Transformation);


	testAnimation.addKeyFrame(keyFrame1);
	testAnimation.addKeyFrame(keyFrame2);
	testAnimation.addKeyFrame(keyFrame3);
	testAnimation.addKeyFrame(keyFrame4);
	testAnimation.addKeyFrame(keyFrame5);
	testAnimation.addKeyFrame(keyFrame6);

	std::vector<Model *> modelList;
	std::vector<testNotification *> notificationClassList;
	std::string animationName = "testAnime";
		for (int i = 0; i < 1; i++) {
		modelList.emplace_back(new Model(modelMeshList));
		modelList.back()->addAnimation(testAnimation, animationName);
		notificationClassList.push_back(new testNotification());
		modelList.back()->registerObserver(notificationClassList.back());
	}

	for (unsigned int i = 0; i < modelList.size(); i++) {
		Model *testModel = modelList[i];
		testModel->scale(glm::vec3(1.0f, 1.0f, 1.0f));
		testModel->translate(glm::vec3(-5.0f + (float) i, 0.0f, 10.0f + (float) i * 3));
	}

	Shader *shaderProgram = new Shader(vertexShaderSource, fragmentShaderSource);
	shaderProgram->bind();

		Camera camera(shaderProgram, 30, 30);
		glm::vec3 cameraRotation(-35, 0, 0);
		camera.rotate(cameraRotation);

		glm::vec3 cameraTrans = glm::vec3(-5.0f + camera.getWidthAndHeight().x / 2, 0.0f, 10.0f);
		cameraTrans.y -= 15;
		cameraTrans.z += 20;
		camera.setTranslationLimits({cameraTrans.x, cameraTrans.y, cameraTrans.z},
									{cameraTrans.x + (40 - camera.getWidthAndHeight().x),
									 cameraTrans.y, cameraTrans.z});
		camera.translate(cameraTrans);
	glEnable(GL_DEPTH_TEST);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------

		AssimpInterpreter interpreter2("cubo.obj", "..");
		std::vector<ModelMesh *> boxList = interpreter2.getModelMeshList();
		Model boxModel(boxList);
		boxModel.scale(glm::vec3(20, 1, 15));
		boxModel.translate(glm::vec3(15, -1.5, 20));

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

		boxModel.draw(*shaderProgram);
		for (unsigned int i = 0; i < modelList.size(); i++) {
			Model *currentModel = modelList[i];
			testNotification *currentNotificationClass = notificationClassList[i];

			currentModel->draw(*shaderProgram);
			camera.update();
			cameraTrans.x = currentModel->getAnimatedTransformation().m_translation.x;
			camera.translate(cameraTrans);
			if (currentModel->getModelTransformation().m_translation.x > 35) {
				currentModel->translate(glm::vec3(-5.0f + (float) i, 0.0f, 10.0f + (float) i * 3));
				camera.animatedMove(0.6, camera.getMinTranslation(), cameraRotation);
			}
			if (currentNotificationClass->m_isActive == false) {
				currentModel->startAnimation(animationName);
				currentNotificationClass->m_isActive = true;

//
//				cameraTrans.x += 0.4;
//				camera.animatedMove(0.41f, cameraTrans, cameraRotation);
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