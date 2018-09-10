//
// Created by Leonard VAN GEND on 2018/09/10.
//

#ifndef LEARNINGOPENGL_ANIMATION_HPP
#define LEARNINGOPENGL_ANIMATION_HPP


#include <vector>
#include "KeyFrame.hpp"

class Animation {
public:
	Animation();
	Animation(const Animation &obj);
	Animation &operator =(const Animation &obj);
	~Animation();

	void addKeyFrame(KeyFrame &keyFrame);
	const Transformation getCurrentTransformation();
	void start();
	void stop();

private:
	unsigned int getRunningTimeInMilliseconds();
	void setKeyFrameIterator(unsigned int runningTimeInMilliseconds);
	float calculateInterpolationValue(unsigned int startTime, unsigned int endTime, unsigned int currentTime);
	std::vector<KeyFrame>::iterator		m_keyFrameIterator;
	std::vector<KeyFrame>				m_keyFrameList;
	unsigned int						m_startTime;
	bool								m_isActive;
};


#endif //LEARNINGOPENGL_ANIMATION_HPP
