#include "OpenGLClasses/openGLFunctionCallErrorManagementWrapper.hpp"
#include "OpenGLClasses/VertexBuffer.hpp"
#include "OpenGLClasses/Shader.hpp"
#include "OpenGLClasses/ElementBuffer.hpp"
#include "extern/stb_image.h"
#include "OpenGLClasses/VertexArray.hpp"
#include <iostream>
#include <SDL.h>
#include <glad/glad.h>
#include <SDL_opengl.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource =	"#version 330 core\n"
									"layout (location = 0) in vec3 aPos;\n"
		 							"layout (location = 1) in vec3 aColor;\n"
									"layout (location = 2) in vec2 aTexCoord;\n"

									"uniform mat4 model;\n"
									"uniform mat4 view;\n"
									"uniform mat4 projection;\n"

		 							"out vec3 ourColor;\n"
									"out vec2 TexCoord;\n"

									"void main()\n"
									"{\n"
									"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
									"	ourColor = aColor;\n"
									"	TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
									"}\0";

const char *fragmentShaderSource = 	"#version 330 core\n"
									"out vec4 FragColor;\n"
									"\n"
									"in vec3 ourColor;\n"
									"in vec2 TexCoord;\n"
									"\n"
									"// texture sampler\n"
									"uniform sampler2D texture1;\n"
									"\n"
									"void main()\n"
									"{\n"
									"	FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);\n"
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
			500, 500, SDL_WINDOW_OPENGL);


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

	float vertices[] = {
			// positions         // colors
			0.5f, -0.5f, 0.0f,  0.2f, 0.8f, 0.6f,	1.0f, 0.0f,// bottom right
			-0.5f, -0.5f, 0.0f,	1.0f, 0.6f, 0.3f,	0.0f, 0.0f,// bottom left
			0.5f,  0.5f, 0.0f,  0.9f, 0.4f, 1.0f,	1.0f, 1.0f,// top right
			-0.5f, 0.5f, 0.0f,	0.4f, 1.0f, 0.5f,	0.0f, 1.0f// top left

	};


	unsigned int indicies[] = {	0, 1, 3,
								0, 2, 3};

	ElementBuffer elementBuffer(sizeof(indicies), indicies, GL_STATIC_DRAW);

	VertexBufferLayout bufferLayout;
	bufferLayout.push(GL_FLOAT, 3);
	bufferLayout.push(GL_FLOAT, 3);
	bufferLayout.push(GL_FLOAT, 2);

	VertexBuffer vertexBuffer(sizeof(vertices), vertices);

	VertexArray vertexArray;
	vertexArray.setElementBuffer(elementBuffer);
	vertexArray.setVertexBuffer(vertexBuffer, bufferLayout);

//	vertexArray.setVertexBuffer(texturePosBuffer, bufferLayout2);
//	vertexArray.setElementBuffer(elementBuffer);



	// load and create a texture
	// -------------------------
	unsigned int texture;
	GL_ERROR_WRAPPER(glGenTextures(1, &texture));
	GL_ERROR_WRAPPER(glBindTexture(GL_TEXTURE_2D, texture)); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	GL_ERROR_WRAPPER(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	// set texture wrapping to GL_REPEAT (default wrapping method)
	GL_ERROR_WRAPPER(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	// set texture filtering parameters
	GL_ERROR_WRAPPER(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_ERROR_WRAPPER(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load("../container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		GL_ERROR_WRAPPER(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
		GL_ERROR_WRAPPER(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	Shader shaderProgram(vertexShaderSource, fragmentShaderSource);
	shaderProgram.bind();
	vertexArray.bind();

	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.1f, -0.6f));

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	shaderProgram.setUniformMatrix4fv("view", glm::value_ptr(view), GL_FALSE);
	shaderProgram.setUniformMatrix4fv("projection", glm::value_ptr(projection), GL_FALSE);
	shaderProgram.setUniformMatrix4fv("model", glm::value_ptr(model), GL_FALSE);

	// render loop
	// -----------
	bool loop = true;
	while (loop)
	{
		// input
		// -----

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				loop = false;
				break;
			}
		}

		// render
		// ------
		GL_ERROR_WRAPPER(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GL_ERROR_WRAPPER(glClear(GL_COLOR_BUFFER_BIT));

		// render the triangle
		GL_ERROR_WRAPPER(glBindTexture(GL_TEXTURE_2D, texture));
		GL_ERROR_WRAPPER(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

		SDL_GL_SwapWindow(GLOBAL_SDL_WINDOW);
	}
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(GLOBAL_SDL_WINDOW);
	SDL_Quit();
	return 0;
}