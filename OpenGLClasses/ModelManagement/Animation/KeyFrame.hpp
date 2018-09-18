//
// Created by Leonard VAN GEND on 2018/09/10.
//

#ifndef LEARNINGOPENGL_KEYFRAME_HPP
#define LEARNINGOPENGL_KEYFRAME_HPP


#include "../Models/Transformation.hpp"

class KeyFrame {
public:
	KeyFrame(float timeStampInSeconds, Transformation keyFrameTransformation);
	KeyFrame(const KeyFrame &obj);
	KeyFrame &operator =(const KeyFrame &obj);
	~KeyFrame();

	const Transformation &getFrameTransformation();
	unsigned int getTimeStampInMilliseconds();

private:
	unsigned int m_timeStampInMilliseconds;
	Transformation	m_keyFrameTransformation;
};


#endif //LEARNINGOPENGL_KEYFRAME_HPP
