//
// Created by Leonard VAN GEND on 2018/09/11.
//

#include "../../Includes/Observable.hpp"

Observable::Observable() {
}

Observable::Observable(const Observable &obj) {
	*this = obj;
}

Observable &Observable::operator=(const Observable &obj) {
	if (this != &obj) {
		this->m_observerList = obj.m_observerList;
	}
	return *this;
}

Observable::~Observable() {
}

void Observable::registerObserver(i_Observer *observer) {
	this->m_observerList.insert(observer);
}

void Observable::unregisterObserver(i_Observer *observer) {
	auto element = this->m_observerList.find(observer);
	if (element != this->m_observerList.end())
		this->m_observerList.erase(element);
}
