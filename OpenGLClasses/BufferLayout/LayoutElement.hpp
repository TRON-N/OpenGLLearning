//
// Created by Leonard VAN GEND on 2018/09/04.
//

#ifndef LEARNINGOPENGL_LAYOUTELEMENT_HPP
#define LEARNINGOPENGL_LAYOUTELEMENT_HPP


class LayoutElement {
public:
	LayoutElement(unsigned int type, unsigned int ammount, bool shouldNormalize);
	~LayoutElement();

	static unsigned int getSizeOfType(unsigned int type);

	unsigned int m_ammount;
	unsigned int m_type;
	unsigned char m_shouldNormalize;
};


#endif //LEARNINGOPENGL_LAYOUTELEMENT_HPP
