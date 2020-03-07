#ifndef PARSER_HPP
#define PARSER_HPP

/**
 * Based on https://shilohjames.wordpress.com/2014/04/27/tinyxml2-tutorial/
 **/

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include "tinyxml2.h"

#include "camera.hpp"
#include "scene.hpp"

using namespace tinyxml2;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult)                    \
    if (a_eResult != XML_SUCCESS)                    \
    {                                                \
        std::cout << "Error: " << a_eResult << "\n"; \
        return a_eResult;                            \
    }
#endif

class Parser
{
private:
    std::string filename;
    XMLDocument xmlDoc;
    XMLNode *pRoot;
    XMLElement *pElement;

public:
    Parser() {}
    Parser(std::string filename) : filename(filename) {}
    ~Parser() {}

    // int extractData(Camera &cam, Film &film, Background &bg);
    int extractData(std::shared_ptr<Camera> &cam, std::shared_ptr<Scene> &scene);
};

int Parser::extractData(std::shared_ptr<Camera> &cam, std::shared_ptr<Scene> &scene)
// int Parser::extractData(Camera &cam, Film &film, Background &bg)
{
    XMLError eResult = xmlDoc.LoadFile(filename.c_str());
    XMLCheckResult(eResult);
    
    // const char* str = "default";
    // int val = 0;
    // std::stringstream sstr;

    pRoot = xmlDoc.FirstChild();
    if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

    cam->parse(pRoot);
    scene->parse(pRoot);

    // // setting camera
    // pElement = pRoot->FirstChildElement("camera");
    // pElement->QueryStringAttribute("type",&str);
    // cam.setType(str);

    // // setting film
    // pElement = pRoot->FirstChildElement("film");
    // pElement->QueryStringAttribute("type",&str);
    // film.type = str;
    // pElement->QueryIntAttribute("x_res",&val);
    // film.x_res = val;
    // pElement->QueryIntAttribute("y_res",&val);
    // film.y_res = val;
    // pElement->QueryStringAttribute("filename",&str);
    // film.filename = str;
    // pElement->QueryStringAttribute("img_type",&str);
    // film.img_type = str;

    // // setting background
    // pElement = pRoot->FirstChildElement("background");
    // pElement->QueryStringAttribute("type",&str);
    // bg.type = str;
    // pElement->QueryStringAttribute("color",&str);
    // sstr << str;
    // float a, b, c;
    // sstr >> a >> b >> c;
    // bg.color = Vector3(a, b, c);
    
    return XML_SUCCESS;
}

#endif