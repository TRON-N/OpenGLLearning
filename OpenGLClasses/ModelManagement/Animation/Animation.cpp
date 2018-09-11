//
// Created by Leonard VAN GEND on 2018/09/10.
//

#include <SDL_timer.h>
#include "Animation.hpp"

Animation::Animation() {

}

Animation::Animation(const Animation &obj) {
	*this = obj;
}

Animation &Animation::operator=(const Animation &obj) {
	if (this != &obj) {
		this->m_isActive = obj.m_isActive;
		this->m_keyFrameList = obj.m_keyFrameList;
		this->m_startTime = obj.m_startTime;
		this->m_keyFrameIterator = obj.m_keyFrameIterator;
	}
	return *this;
}

Animation::~Animation() {

}

void Animation::addKeyFrame(KeyFrame &keyFrame) {
	if (this->m_keyFrameList.size() > 0)
		assert(this->m_keyFrameList.back().getTimeStampInMilliseconds() < keyFrame.getTimeStampInMilliseconds());
	this->m_keyFrameList.push_back(keyFrame);
}

const Transformation Animation::getCurrentTransformation() {
	if (this->m_isActive) {
		unsigned int currentTime = this->getRunningTimeInMilliseconds();

		this->setKeyFrameIterator(currentTime);

		if (this->m_keyFrameIterator != this->m_keyFrameList.end() &&
			this->m_keyFrameIterator + 1 != this->m_keyFrameList.end()) {
			KeyFrame &previousKeyFrame = *(this->m_keyFrameIterator);
			KeyFrame &nextKeyFrame = *(this->m_keyFrameIterator + 1);

			float interpolationValue = this->calculateInterpolationValue(
					previousKeyFrame.getTimeStampInMilliseconds(),
					nextKeyFrame.getTimeStampInMilliseconds(),
					currentTime);

			Transformation interpolatedTransformation = Transformation::getInterpolatedTransformation(
					previousKeyFrame.getFrameTransformation(),
					nextKeyFrame.getFrameTransformation(),
					interpolationValue);

			return interpolatedTransformation;
		}
	}

	this->m_isActive = false;
	this->notifyObservers();
	return Transformation();
}

void Animation::start() {
	this->m_startTime = SDL_GetTicks();
	this->m_keyFrameIterator = this->m_keyFrameList.begin();
	this->m_isActive = true;
}

void Animation::stop() {
	this->m_isActive = false;
}

unsigned Animation::getRunningTimeInMilliseconds() {
	return SDL_GetTicks() - this->m_startTime;
}

void Animation::setKeyFrameIterator(unsigned int runningTimeInMilliseconds) {
	if (this->m_keyFrameIterator == this->m_keyFrameList.end())
		return;

	KeyFrame &nextKeyFrame = *(this->m_keyFrameIterator + 1);

	if (nextKeyFrame.getTimeStampInMilliseconds() < runningTimeInMilliseconds) {
		this->m_keyFrameIterator++;
		this->setKeyFrameIterator(runningTimeInMilliseconds);
	}
}

float Animation::calculateInterpolationValue(unsigned int startTime, unsigned int endTime,
													  unsigned int currentTime) {
	unsigned int maximumTimeDifference = endTime - startTime;
	unsigned int actualTimeDifference = currentTime - startTime;

	float interpolationValue = (float)actualTimeDifference / (float)maximumTimeDifference;
	return (interpolationValue);
}

void Animation::notifyObservers() {
	for (i_Observer *observer: this->m_observerList)
		observer->notify(nullptr);
}

const Transformation Animation::getFinalTransformation() {
	return this->m_keyFrameList.back().getFrameTransformation();
}


