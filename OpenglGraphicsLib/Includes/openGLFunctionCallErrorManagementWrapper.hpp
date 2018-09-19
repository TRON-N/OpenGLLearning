//
// Created by Leonard on 2018/08/29.
//

#ifndef LEARNINGOPENGL_OPENGLFUNCTIONCALLWRAPPER_HPP
#define LEARNINGOPENGL_OPENGLFUNCTIONCALLWRAPPER_HPP

#include <cassert>


void clearGLErrors();

int checkForGLErrors();

#define GL_ERROR_WRAPPER(x) clearGLErrors(); x; assert(checkForGLErrors() == 0)

#endif //LEARNINGOPENGL_OPENGLFUNCTIONCALLWRAPPER_HPP
