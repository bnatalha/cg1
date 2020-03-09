#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "header.hpp"
#include "vector3.hpp"
#include "tinyxml2.h"

// using namespace tinyxml2;
using std::string;

/**
 * Is responsible for returning a color each time the primary ray misses any object in the scene (i.e. hits nothing).
 * */
class Background
{
public:
    bool hasCornerColors;
    std::string type;
    std::string mapping;
    rgb color;
    rgb bl; // (0,0)
    rgb tl; // (0,1)
    rgb tr; // (1,1)
    rgb br; // (1,0)

    Background(){}
    Background(bool corner, string t, string mp, string c, string mBL, string mTL, string mTR, string mBR) : hasCornerColors(corner), type(t), mapping(mp), color(c.c_str()) 
    {
        bl = rgb(hasCornerColors? mBL.c_str() : DEFAULT_COLOR);
        tl = rgb(hasCornerColors? mTL.c_str() : DEFAULT_COLOR);
        tr = rgb(hasCornerColors? mTR.c_str() : DEFAULT_COLOR);
        br = rgb(hasCornerColors? mBR.c_str() : DEFAULT_COLOR);
    
    }
    ~Background(){}

    inline rgb sample (float x, float y)
    {
        if(!hasCornerColors)
        {
            return color;
        }

        // formula:
        rgb bl; // (0,0)
        rgb tl; // (0,1)
        rgb tr; // (1,1)
        rgb br; // (1,0)

        auto r = bl*(1-x)*(1-y)
            + br*x*(1-y)
            + tl*(1-x)*y
            + tr*x*y;

        return r;
    }

    inline void print()
    {
        std::cout << "background: ["
            << (hasCornerColors ? "" : "!") << "hasProvidedCorners" << " "
            << type << " "
            << mapping << " "
            << color << "\n"
            << bl << "\n"
            << tl << "\n"
            << tr << "\n"
            << br << "]\n";
    }

    // inline int parse(XMLNode *pRoot)
    // {
    //     const char* str = "default";
    //     XMLElement *pElement;

    //     pElement = pRoot->FirstChildElement("background");
    //     pElement->QueryStringAttribute("type", &str);
    //     type = str;
    //     pElement->QueryStringAttribute("color", &str);
    //     color = Vector3(str);

    //     return XML_SUCCESS;
    // }
};

#endif