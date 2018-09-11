//
// Created by Leonard VAN GEND on 2018/09/11.
//

#ifndef LEARNINGOPENGL_OBSERVABLE_HPP
#define LEARNINGOPENGL_OBSERVABLE_HPP

#include <set>
#include "i_Observer.hpp"

class Observable {
public:
	Observable();
	Observable(const Observable &obj);
	Observable &operator=(const Observable &obj);
	virtual ~Observable();

	void registerObserver(i_Observer *observer);
	void unregisterObserver(i_Observer *observer);

	virtual void notifyObservers() = 0;

protected:
	std::set<i_Observer *>	m_observerList;
};


#endif //LEARNINGOPENGL_OBSERVABLE_HPP
