//
// Created by Leonard VAN GEND on 2018/09/04.
//

#ifndef LEARNINGOPENGL_VERTEXBUFFERLAYOUT_HPP
#define LEARNINGOPENGL_VERTEXBUFFERLAYOUT_HPP

#include <vector>
#include "LayoutElement.hpp"

class VertexBufferLayout {
public:
	VertexBufferLayout();
	~VertexBufferLayout();
	const std::vector<LayoutElement>& getLayoutElements();

	void push(unsigned int type, unsigned count, bool shouldNormalize = false);
	unsigned int getStrideLength();

private:
	unsigned int m_strideLength;
	std::vector<LayoutElement> m_layoutElements;

};
#endif //LEARNINGOPENGL_VERTEXBUFFERLAYOUT_HPP
