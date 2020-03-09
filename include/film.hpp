#ifndef FILM_HPP
#define FILM_HPP

#include <iostream>
#include <vector>
#include <memory>

#include "tinyxml2.h"

using namespace tinyxml2;

/**
 * Handles pixels values as an image color buffer. This allows the ray tracer to save the color buffer to an image file in PPM or PNG format.
 * */
class Film
{
public:
    std::string type;
    int y_res;
    int x_res;
    std::string filename;
    std::string img_type;

    // std::shared_ptr<std::vector<int>> buffer;
    std::vector<int> buffer;

    Film() {}
    Film(std::string t, int y, int x, std::string fn, std::string imgt) : type(t), y_res(y), x_res(x), filename(fn), img_type(imgt)  {}
    ~Film() {}

    // void init(){
        // buffer = std::make_shared<std::vector<int>>();
        // buffer->reserve(y_res * x_res);
    // }

    inline void print()
    {
        std::cout
            << type << " "
            << x_res << " "
            << y_res << " "
            << filename << " "
            << img_type << "\n";
    }

    // inline int parse(XMLNode *pRoot)
    // {
    //     const char* str = "default";
    //     int val;
    //     XMLElement *pElement;

    //     pElement = pRoot->FirstChildElement("film");
    //     pElement->QueryStringAttribute("type", &str);
    //     type = str;
    //     pElement->QueryIntAttribute("x_res", &val);
    //     x_res = val;
    //     pElement->QueryIntAttribute("y_res", &val);
    //     y_res = val;
    //     pElement->QueryStringAttribute("filename", &str);
    //     filename = str;
    //     pElement->QueryStringAttribute("img_type", &str);
    //     img_type = str;

    //     return XML_SUCCESS;
    // }
};

#endif