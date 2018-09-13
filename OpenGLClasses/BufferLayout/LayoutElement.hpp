//
// Created by Leonard VAN GEND on 2018/09/04.
//

#ifndef LEARNINGOPENGL_LAYOUTELEMENT_HPP
#define LEARNINGOPENGL_LAYOUTELEMENT_HPP


class LayoutElement {
public:
	LayoutElement(unsigned int type, unsigned int amount, bool shouldNormalize);
	LayoutElement();
	LayoutElement(const LayoutElement &obj);
	LayoutElement &operator=(const LayoutElement &obj);
	~LayoutElement();

	static unsigned int getSizeOfType(unsigned int type);

	unsigned int m_amount;
	unsigned int m_type;
	bool m_shouldNormalize;
};


#endif //LEARNINGOPENGL_LAYOUTELEMENT_HPP
