#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include "tinyxml2.h"
#include "film.hpp"
#include "paramset.hpp"

using namespace tinyxml2;

namespace rt3 {

    using std::unique_ptr;
    using std::vector;
    using std::unordered_map;
    using std::string;

    class Camera
    {
    public:
        std::string type;
        Film film;

        Camera() {}
        Camera(string t) : type(t) {}
        ~Camera() {}

        // inline int parse(XMLNode *pRoot)
        // {
        //     const char* str = "default"; 
        //     XMLElement *pElement;
            
        //     // setting camera
        //     pElement = pRoot->FirstChildElement("camera");
        //     pElement->QueryStringAttribute("type", &str);
        //     type = str;

        //     // setting film
        //     return film.parse(pRoot);
        // }

        inline void print(){
            std::cout << "Camera type: " << type << "\n";
            film.print();
        }
    };

}

#endif