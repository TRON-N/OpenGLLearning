//
// Created by Leonard VAN GEND on 2018/09/17.
//

#ifndef LEARNINGOPENGL_RENDERER_HPP
#define LEARNINGOPENGL_RENDERER_HPP


#include "i_Observer.hpp"
#include "Shader.hpp"

class Renderer : public i_Observer {
public:
	Renderer(SDL_Window *window);
	Renderer();
	Renderer(const Renderer &obj);
	Renderer &operator=(const Renderer &obj);
	~Renderer();

	void update();
	void notify(void *arg) override;

	Shader &getShaderProgram();


private:
	SDL_Window *m_window;
	SDL_GLContext m_glContext;
	Shader *m_shaderProgram;

	static const char *m_vertexShaderSource;
	static const char *m_fragmentShaderSource;
};


#endif //LEARNINGOPENGL_RENDERER_HPP
