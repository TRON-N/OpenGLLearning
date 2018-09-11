//
// Created by Leonard VAN GEND on 2018/09/11.
//

#ifndef LEARNINGOPENGL_I_OBSERVER_HPP
#define LEARNINGOPENGL_I_OBSERVER_HPP

class i_Observer {
public:
	virtual void notify(void *arg) = 0;
};

#endif //LEARNINGOPENGL_I_OBSERVER_HPP
