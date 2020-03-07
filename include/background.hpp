#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "vector3.hpp"
#include "tinyxml2.h"

using namespace tinyxml2;

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

    inline void print()
    {
        std::cout
            << type << " "
            << color << "\n";
    }
    inline int parse(XMLNode *pRoot)
    {
        const char* str = "default";
        XMLElement *pElement;

        pElement = pRoot->FirstChildElement("background");
        pElement->QueryStringAttribute("type", &str);
        type = str;
        pElement->QueryStringAttribute("color", &str);
        color = Vector3(str);

        return XML_SUCCESS;
    }
};

#endif