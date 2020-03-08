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

#include "api.hpp"
#include "paramset.hpp"

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
    const std::string filename;
    XMLDocument xmlDoc;
    XMLNode *pRoot;
    XMLElement *pElement;

public:
    Parser() {}
    Parser(std::string filename) : filename(filename) {}
    ~Parser() {}

    // int extractData(Camera &cam, Film &film, Background &bg);
    // int extractData();

    int extractData(rt3::API &api);

    // fazer unique_ptr de array de strings
    inline void addStrAttr(XMLElement *pE, const char* tag, rt3::ParamSet &ps){
        const char* str = "default";
        pElement->QueryStringAttribute(tag,&str);
        std::unique_ptr<std::string []> u_ptr (new std::string[1]);
        u_ptr[0] = str;
        ps.add(tag, std::move(u_ptr), 1);
    }

    inline void addIntAttr(XMLElement *pE, const char* tag, rt3::ParamSet &ps){
        int val = 0;
        pElement->QueryIntAttribute(tag,&val);
        std::unique_ptr<std::string []> u_ptr (new std::string[1]);
        u_ptr[0] = std::to_string(val);
        ps.add(tag, std::move(u_ptr), 1);
        // return std::string(val);
    }
};

int Parser::extractData(rt3::API &api)
// int Parser::extractData(Camera &cam, Film &film, Background &bg)
{
    rt3::ParamSet ps;
    // const char* str = "default";
    // int val = 0;
    // std::stringstream sstr;

    XMLError eResult = xmlDoc.LoadFile(filename.c_str());
    XMLCheckResult(eResult);

    pRoot = xmlDoc.FirstChild();
    if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

    // cam->parse(pRoot);
    // scene->parse(pRoot);

    // setting camera
    pElement = pRoot->FirstChildElement("camera");
    addStrAttr(pElement, "type", ps);

    api.camera(ps);
    ps.clear();

    // setting film
    pElement = pRoot->FirstChildElement("film");

    addStrAttr(pElement, "type", ps);
    addIntAttr(pElement, "x_res", ps);
    addIntAttr(pElement, "y_res", ps);
    addStrAttr(pElement, "filename", ps);
    addStrAttr(pElement, "img_type", ps);

    api.camera_film(ps);
    ps.clear();

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