//
// Created by Leonard on 2018/08/29.
//

#ifndef LEARNINGOPENGL_ELEMENTBUFFER_HPP
#define LEARNINGOPENGL_ELEMENTBUFFER_HPP

class ElementBuffer {
public:
	ElementBuffer(unsigned int size, void *data, int drawOption);
	~ElementBuffer();
	void bind();
	void unbind();
private:
	unsigned int m_bufferId;
};


#endif //LEARNINGOPENGL_ELEMENTBUFFER_HPP
