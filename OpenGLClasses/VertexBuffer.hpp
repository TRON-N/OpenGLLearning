//
// Created by Leonard on 2018/08/29.
//

#ifndef LEARNINGOPENGL_VERTEXBUFFER_HPP
#define LEARNINGOPENGL_VERTEXBUFFER_HPP


class VertexBuffer {
public:
	VertexBuffer(unsigned int size, void *data);
	~VertexBuffer();
	void bind();
	void unbind();
private:
	unsigned int m_bufferId;

};


#endif //LEARNINGOPENGL_VERTEXBUFFER_HPP
