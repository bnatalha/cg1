#ifndef SCENE_HPP
#define SCENE_HPP

#include "tinyxml2.hpp"
#include "background.hpp"

namespace rt3 {
using namespace tinyxml2;

class Scene
{
public:
    Background background;

    Scene() {}
    Scene(Background &bg) : background(bg) {}
    ~Scene() {}

    inline void print() {
        background.print();
    }
};

}

#endif