#ifndef API_HPP
#define API_HPP

#include "camera.hpp"
#include "scene.hpp"

/**
 * Is responsible for returning a color each time the primary ray misses any object in the scene (i.e. hits nothing).
 * */
class API
{
public:

    Camera camera;
    Scene scene;

    API(){}
    ~API(){}
};

#endif