//
// Created by Leonard on 2018/08/29.
//

#ifndef LEARNINGOPENGL_VERTEXBUFFER_HPP
#define LEARNINGOPENGL_VERTEXBUFFER_HPP


class VertexBuffer {
public:
	VertexBuffer(unsigned int size, void *data);
	VertexBuffer();
	~VertexBuffer();

	void bind();
	static void unbind();
private:
	unsigned int m_vertexBufferId;

};


#endif //LEARNINGOPENGL_VERTEXBUFFER_HPP
