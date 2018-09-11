#include <SDL.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "OpenGLClasses/ModelManagement/AssimpInterperater/AssimpInterperater.hpp"
#include "extern/stb_image.h"
#include "OpenGLClasses/Shader.hpp"
#include "OpenGLClasses/openGLFunctionCallErrorManagementWrapper.hpp"
#include "OpenGLClasses/ModelManagement/Models/Model.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource =	"#version 330 core\n"
									"layout (location = 0) in vec3 aPos;\n"

									"uniform mat4 model;\n"
									"uniform mat4 view;\n"
									"uniform mat4 projection;\n"

		 							"out vec3 ourColor;\n"

									"void main()\n"
									"{\n"
									"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
									"	ourColor = vec3(0.5, 1.0, 0.3);\n"
									"}\0";

const char *fragmentShaderSource = 	"#version 330 core\n"
									"out vec4 FragColor;\n"
									"\n"
									"in vec3 ourColor;\n"
									"\n"
									"// texture sampler\n"
									"uniform sampler2D texture1;\n"
									"uniform sampler2D texture2;\n"
									"\n"
									"void main()\n"
									"{\n"
									"	FragColor = vec4(ourColor, 1.0);\n"
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

int main(int argc, char *argv[])
{
	if(argc == 0 && argv == nullptr)
		std::cout << "no args" << std::endl;

	createSDLWindow();
	SDL_GLContext gl_context = SDL_GL_CreateContext(GLOBAL_SDL_WINDOW);

	if (!gladLoadGLLoader((SDL_GL_GetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	AssimpInterperater interperater("../BomberBoi.obj");
	std::vector<ModelMesh *> modelMeshList = interperater.getModelMeshList();
	Model testModel(modelMeshList);

	Animation testAnimation;

	Transformation keyFrame1Transformation;
	KeyFrame keyFrame1(0.0f, keyFrame1Transformation);

	Transformation keyFrame2Transformation;
	keyFrame2Transformation.m_translation = glm::vec3(0, 0.25, 0);
	KeyFrame keyFrame2(0.25f, keyFrame2Transformation);

	Transformation keyFrame3Transformation;
	keyFrame3Transformation.m_translation = glm::vec3(0.5, 0, 0);
	KeyFrame keyFrame3(0.5f, keyFrame3Transformation);

	testAnimation.addKeyFrame(keyFrame1);
	testAnimation.addKeyFrame(keyFrame2);
	testAnimation.addKeyFrame(keyFrame3);

	std::string animationName = "testAnime";
	testModel.addAnimation(testAnimation, "testAnime");

	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.5f));

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(55.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	testModel.scale(glm::vec3(1.7f, 1.7f, 1.7f));
	testModel.translate(glm::vec3(-1.0f, -1.0f, 0.0f));

	Shader shaderProgram(vertexShaderSource, fragmentShaderSource);
	shaderProgram.bind();
	shaderProgram.setUniformMatrix4fv("view", glm::value_ptr(view), GL_FALSE);
	shaderProgram.setUniformMatrix4fv("projection", glm::value_ptr(projection), GL_FALSE);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
//	testModel.startAnimation("testAnime");

	bool loop = true;
	while (loop)
	{

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				loop = false;
				break;
			}
		}

		GL_ERROR_WRAPPER(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GL_ERROR_WRAPPER(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ));

//		float angle = 20.0f * 2;
//		testModel.rotate(glm::vec3(0, SDL_GetTicks() / angle, 0));
		testModel.draw(shaderProgram);

		SDL_GL_SwapWindow(GLOBAL_SDL_WINDOW);
	}
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(GLOBAL_SDL_WINDOW);
	SDL_Quit();
	std::cout << "Program Ended" << std::endl;
	return 0;
}