#ifndef SCENE_HPP
#define SCENE_HPP

#include "tinyxml2.h"

#include "background.hpp"

using namespace tinyxml2;

class Scene
{
public:
    Background background;

    Scene() {}
    Scene(Background &bg) : background(bg) {}
    ~Scene() {}

    // inline int parse(XMLNode *pRoot)
    // {
    //     return background.parse(pRoot);
    // }

    inline void print() {
        background.print();
    }
};

#endif