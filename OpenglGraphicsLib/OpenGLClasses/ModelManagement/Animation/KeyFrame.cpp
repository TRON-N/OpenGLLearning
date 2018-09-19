//
// Created by Leonard VAN GEND on 2018/09/10.
//

#include "../../../Includes/KeyFrame.hpp"

KeyFrame::KeyFrame(float timeStampInSeconds, Transformation keyFrameTransformation) :
		m_keyFrameTransformation(keyFrameTransformation){
	this->m_timeStampInMilliseconds = timeStampInSeconds * 1000.0f;
}

KeyFrame::KeyFrame(const KeyFrame &obj) {
	*this = obj;
}

KeyFrame &KeyFrame::operator=(const KeyFrame &obj) {
	if (this != &obj) {
		this->m_keyFrameTransformation = obj.m_keyFrameTransformation;
		this->m_timeStampInMilliseconds = obj.m_timeStampInMilliseconds;
	}
	return *this;
}

KeyFrame::~KeyFrame() {
}

unsigned int KeyFrame::getTimeStampInMilliseconds() {
	return this->m_timeStampInMilliseconds;
}

const Transformation &KeyFrame::getFrameTransformation() {
	return this->m_keyFrameTransformation;
}
