//
// Created by Leonard on 2018/08/29.
//

#ifndef LEARNINGOPENGL_VERTEXARRAY_HPP
#define LEARNINGOPENGL_VERTEXARRAY_HPP


#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include "BufferLayout/VertexBufferLayout.hpp"

class VertexArray {
public:
	VertexArray();
	VertexArray(VertexArray &obj);
	VertexArray &operator = (const VertexArray& obj);
	~VertexArray();

	void setVertexBuffer(VertexBuffer &vbo, VertexBufferLayout &bufferLayout);
	void setElementBuffer(ElementBuffer &ebo);
	void unsetElementBuffer();
	void bind();
	static void unbind();

private:
	unsigned int m_vertexArrayId;
	unsigned int m_attribPointerId;
};


#endif //LEARNINGOPENGL_VERTEXARRAY_HPP
