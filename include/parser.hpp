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
        std::cerr << "XMLError while parsing: " << a_eResult << "\n"; \
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
    Parser(std::string filename) : filename(filename) 
    {
        
    }
    ~Parser() {}

    int extractData(rt3::API &api);

    inline void addStrAttr(XMLElement *pE, const char* tag, rt3::ParamSet &ps){
        const char* str = "not_found";
        auto xmlResult = pElement->QueryStringAttribute(tag,&str);
        if(xmlResult != XML_SUCCESS) {return;} // value not found
        std::unique_ptr<std::string []> u_ptr (new std::string[1]);
        u_ptr[0] = str;
        ps.add<std::string>(tag, std::move(u_ptr), 1);
    }

    inline void addIntAttr(XMLElement *pE, const char* tag, rt3::ParamSet &ps){
        int val = -42;  // default not_found value;
        auto xmlResult = pElement->QueryIntAttribute(tag,&val);
        if(xmlResult != XML_SUCCESS) {return;} // value not found
        std::unique_ptr<int []> u_ptr (new int[1]);
        u_ptr[0] = val;
        ps.add<int>(tag, std::move(u_ptr), 1);
    }
};

int Parser::extractData(rt3::API &api)
{
    rt3::ParamSet ps;

    XMLError eResult = xmlDoc.LoadFile(filename.c_str());
    XMLCheckResult(eResult);

    pRoot = xmlDoc.FirstChild();
    if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

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

    // setting background
    pElement = pRoot->FirstChildElement("background");
    
    addStrAttr(pElement, "type", ps);
    addStrAttr(pElement, "mapping", ps);
    addStrAttr(pElement, "color", ps);
    addStrAttr(pElement, "bl", ps);
    addStrAttr(pElement, "tl", ps);
    addStrAttr(pElement, "tr", ps);
    addStrAttr(pElement, "br", ps);

    api.scene(ps);
    ps.clear();
    
    return XML_SUCCESS;
}

#endif