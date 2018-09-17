//
// Created by Leonard VAN GEND on 2018/09/17.
//

#ifndef LEARNINGOPENGL_RENDERER_HPP
#define LEARNINGOPENGL_RENDERER_HPP


class Renderer {
public:
	Renderer(SDL_Window *window);

	~Renderer();

	void update();

private:
	SDL_Window *m_window;
	SDL_GLContext m_glContext;
};


#endif //LEARNINGOPENGL_RENDERER_HPP
