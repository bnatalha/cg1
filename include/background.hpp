#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "vector3.hpp"

/**
 * Is responsible for returning a color each time the primary ray misses any object in the scene (i.e. hits nothing).
 * */
class Background
{
public:
    std::string type;
    Vector3 color;

    Background(){};
    ~Background(){};

    inline void print(){
        std::cout 
            << type << " "
            << color << "\n";
    }
};

#endif