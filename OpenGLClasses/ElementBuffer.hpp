//
// Created by Leonard on 2018/08/29.
//

#ifndef LEARNINGOPENGL_ELEMENTBUFFER_HPP
#define LEARNINGOPENGL_ELEMENTBUFFER_HPP

class ElementBuffer {
public:
	ElementBuffer(unsigned int size, void *data, int drawOption);
	ElementBuffer();
	ElementBuffer(const ElementBuffer& obj);
	ElementBuffer &operator =(const ElementBuffer& obj);
	~ElementBuffer();

	void setUpForVertexArray();
	void bind();
	static void unbind();

private:
	unsigned int	m_elementBufferId;

	unsigned int	m_dataSize;
	void *			m_data;
	int 			m_drawOption;
};


#endif //LEARNINGOPENGL_ELEMENTBUFFER_HPP
