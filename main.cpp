#include <SDL.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "OpenGLClasses/ModelManagement/AssimpInterperater/AssimpInterperater.hpp"
#include "extern/stb_image.h"
#include "OpenGLClasses/Shader.hpp"
#include "OpenGLClasses/openGLFunctionCallErrorManagementWrapper.hpp"

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
	createSDLWindow();
	SDL_GLContext gl_context = SDL_GL_CreateContext(GLOBAL_SDL_WINDOW);

	if (!gladLoadGLLoader((SDL_GL_GetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	AssimpInterperater interperater("../BomberBoi.obj");
	std::vector<ModelMesh *> modelMeshList = interperater.getModelMeshList();

	unsigned int texture1, texture2;
	// texture 1
	// ---------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load("../container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// texture 2
	// ---------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load("../awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	Shader shaderProgram(vertexShaderSource, fragmentShaderSource);
	shaderProgram.bind();
	shaderProgram.setUniformInt("texture1", 0);
	shaderProgram.setUniformInt("texture2", 1);

	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.5f));

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(55.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		for (auto model: modelMeshList) {
			model->scale(1.7f, 1.7f, 1.7f);
			model->translate(0.0f, -1.0f, 0.0f);
		}

	shaderProgram.setUniformMatrix4fv("view", glm::value_ptr(view), GL_FALSE);
	shaderProgram.setUniformMatrix4fv("projection", glm::value_ptr(projection), GL_FALSE);

	glm::vec3 cubePositions[] = {
			glm::vec3( 1.0f,  -0.5f,  0.0f),
			glm::vec3( 2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -3.0f, -12.3f),
			glm::vec3( 2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3( 5.3f, -1.0f, -2.5f),
			glm::vec3(-2.5f,  2.0f, -2.5f),
			glm::vec3(-4.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
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

		for(auto model: modelMeshList)
		{
			model->getVertexArray().bind();
			float angle = 20.0f * 2;
			model->rotate(0, SDL_GetTicks() / angle * 5, 0);
			shaderProgram.setUniformMatrix4fv("model", glm::value_ptr(model->getModelToWorldMatrix()), GL_FALSE);
			glDrawElements(GL_TRIANGLES, model->getVertexAmount(), GL_UNSIGNED_INT, 0);;
		}
		SDL_GL_SwapWindow(GLOBAL_SDL_WINDOW);
	}
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(GLOBAL_SDL_WINDOW);
	SDL_Quit();
	return 0;
}