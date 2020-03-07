#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include "tinyxml2.h"
#include "film.hpp"

using namespace tinyxml2;

class Camera
{
public:
    std::string type;
    Film film;

    Camera() {}
    Camera(const char *type) : type(type) {}
    ~Camera() {}

    inline std::string getType() { return type; }
    inline void setType(std::string nType) { type = nType; }
    inline int parse(XMLNode *pRoot)
    {
        const char* str = "default"; 
        XMLElement *pElement;
        
        // setting camera
        pElement = pRoot->FirstChildElement("camera");
        pElement->QueryStringAttribute("type", &str);
        type = str;

        // setting film
        return film.parse(pRoot);
    }

    inline void print(){
        std::cout << "Camera type: " << type << "\n";
        film.print();
    }
};

#endif