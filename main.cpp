#include "OpenGLClasses/openGLFunctionCallErrorManagementWrapper.hpp"
#include "OpenGLClasses/VertexBuffer.hpp"
#include "OpenGLClasses/Shader.hpp"
#include "OpenGLClasses/ElementBuffer.hpp"
#include "stb_image.h"
#include <iostream>
#include <SDL.h>
#include <glad/glad.h>
#include <SDL_opengl.h>
#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource =	"#version 330 core\n"
									"layout (location = 0) in vec3 aPos;\n"
		 							"layout (location = 1) in vec3 aColor;\n"
									"layout (location = 2) in vec2 aTexCoord;\n"

		 							"out vec3 ourColor;\n"
									"out vec2 TexCoord;\n"

									"void main()\n"
									"{\n"
									"	gl_Position = vec4(aPos, 1.0);\n"
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
									"	FragColor = texture(texture1, TexCoord);\n"
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

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((SDL_GL_GetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
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

	unsigned int VAO;
	GL_ERROR_WRAPPER(glGenVertexArrays(1, &VAO));
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	GL_ERROR_WRAPPER(glBindVertexArray(VAO));

	VertexBuffer vbo(sizeof(vertices), vertices);
	vbo.bind();

	// position attribute
	GL_ERROR_WRAPPER(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
	GL_ERROR_WRAPPER(glEnableVertexAttribArray(0));

	// color attribute
	GL_ERROR_WRAPPER(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
	GL_ERROR_WRAPPER(glEnableVertexAttribArray(1));

	// texture coord attribute
	GL_ERROR_WRAPPER(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))));
	GL_ERROR_WRAPPER(glEnableVertexAttribArray(2));


	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);

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


	// as we only have a single shader, we could also just activate our shader once beforehand if we want to
	Shader shaderProgram(vertexShaderSource, fragmentShaderSource);
	shaderProgram.bind();
	elementBuffer.bind();

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
		GL_ERROR_WRAPPER(glBindVertexArray(VAO));
		elementBuffer.bind();
		GL_ERROR_WRAPPER(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		SDL_GL_SwapWindow(GLOBAL_SDL_WINDOW);
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	GL_ERROR_WRAPPER(glDeleteVertexArrays(1, &VAO));

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	SDL_GL_DeleteContext(gl_context);

	// Destroy our window
	SDL_DestroyWindow(GLOBAL_SDL_WINDOW);

	// Shutdown SDL 2
	SDL_Quit();
	return 0;
}