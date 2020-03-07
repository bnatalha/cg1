#ifndef API_HPP
#define API_HPP

#include <memory>

#include "camera.hpp"
#include "scene.hpp"

/**
 * Is responsible for returning a color each time the primary ray misses any object in the scene (i.e. hits nothing).
 * */
class API
{
public:

    std::shared_ptr<Camera> camera;
    std::shared_ptr<Scene> scene;

    API(){
        camera = std::make_shared<Camera>();
        scene = std::make_shared<Scene>();
    }
    ~API(){}
    inline void print(){
        camera->print();
        scene->print();
    }
    
};

#endif