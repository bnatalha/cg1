#ifndef PARSER_HPP
#define PARSER_HPP

/**
 * Based on https://shilohjames.wordpress.com/2014/04/27/tinyxml2-tutorial/
 **/

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include "tinyxml2.hpp"

#include "api.hpp"
#include "parser_tags.hpp"
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
    XMLNode* pRoot;
    XMLElement* pElement;

public:
    Parser() {}
    Parser(std::string filename) : filename(filename) {}
    ~Parser() {}

    int extractData(rt3::API& api);

    inline void addStrAttr(XMLElement* pE, const char* tag, rt3::ParamSet& ps) {
        // const char * str= ParserTags::PARSER_DEFAULT_STR;
        auto xmlResult = pElement->QueryStringAttribute(tag, &ParserTags::PARSER_DEFAULT_STR);
        if (xmlResult != XML_SUCCESS) { return; } // value not found
        std::unique_ptr<std::string[]> u_ptr(new std::string[1]);
        u_ptr[0] = ParserTags::PARSER_DEFAULT_STR;
        ps.add<std::string>(tag, std::move(u_ptr), 1);
    }

    inline void addTag(const char* tag, rt3::ParamSet& ps) {
        std::unique_ptr<bool[]> u_ptr(new bool[1]);
        u_ptr[0] = true;
        ps.add<bool>(tag, std::move(u_ptr), 1);
    }

    inline void addIntAttr(XMLElement* pE, const char* tag, rt3::ParamSet& ps) {
        int val = ParserTags::PARSER_DEFAULT_INT;
        auto xmlResult = pElement->QueryIntAttribute(tag, &val);
        if (xmlResult != XML_SUCCESS) { return; }
        std::unique_ptr<int[]> u_ptr(new int[1]);
        u_ptr[0] = val;
        ps.add<int>(tag, std::move(u_ptr), 1);
    }

    // inline void addPoint3FloatAttr(XMLElement* pE, const char* tag, rt3::ParamSet& ps) {
    //     float[4] val = {-1.0, -1.0, -1.0, -1.0};
    //     auto xmlResult = pElement->QueryIntAttribute(tag, &val);
    //     if (xmlResult != XML_SUCCESS) { return; }
    //     std::unique_ptr<int[]> u_ptr(new int[1]);
    //     u_ptr[0] = val;
    //     ps.add<int>(tag, std::move(u_ptr), 1);
    // }
};

// TODO(bnatalha): refact (a function for each class)
int Parser::extractData(rt3::API& api)
{
    rt3::ParamSet ps;

    XMLError eResult = xmlDoc.LoadFile(filename.c_str());
    XMLCheckResult(eResult);

    pRoot = xmlDoc.FirstChild();
    if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

    // setting camera
    pElement = pRoot->FirstChildElement(ParserTags::CAMERA);
    addStrAttr(pElement, ParserTags::CAMERA_TYPE, ps);
    addStrAttr(pElement, ParserTags::CAMERA_SCREEN_WINDOW, ps);
    addIntAttr(pElement, ParserTags::CAMERA_FOVY, ps);
    pElement = pRoot->FirstChildElement(ParserTags::LOOKAT);
    if (pElement != nullptr) {
        addTag(ParserTags::LOOKAT, ps);
        addStrAttr(pElement, ParserTags::LOOKAT_LOOK_AT, ps);
        addStrAttr(pElement, ParserTags::LOOKAT_LOOK_FROM, ps);
        addStrAttr(pElement, ParserTags::LOOKAT_UP, ps);
    }

    api.camera(ps);
    ps.clear();

    // setting film
    pElement = pRoot->FirstChildElement(ParserTags::FILM);

    addStrAttr(pElement, ParserTags::FILM_TYPE, ps);
    addIntAttr(pElement, ParserTags::FILM_X_RES, ps);
    addIntAttr(pElement, ParserTags::FILM_Y_RES, ps);
    addStrAttr(pElement, ParserTags::FILM_FILENAME, ps);
    addStrAttr(pElement, ParserTags::FILM_IMG_TYPE, ps);
    addStrAttr(pElement, ParserTags::FILM_CROP_WINDOW, ps); // new
    addStrAttr(pElement, ParserTags::FILM_GAMMA_CORRECTED, ps); // new

    api.camera_film(ps);
    ps.clear();

    // setting background
    pElement = pRoot->FirstChildElement(ParserTags::BACKGROUND);

    addStrAttr(pElement, ParserTags::BACKGROUND_TYPE, ps);
    addStrAttr(pElement, ParserTags::BACKGROUND_MAPPING, ps);
    addStrAttr(pElement, ParserTags::BACKGROUND_COLOR, ps);
    addStrAttr(pElement, ParserTags::BACKGROUND_BL, ps);
    addStrAttr(pElement, ParserTags::BACKGROUND_TL, ps);
    addStrAttr(pElement, ParserTags::BACKGROUND_TR, ps);
    addStrAttr(pElement, ParserTags::BACKGROUND_BR, ps);

    api.scene(ps);
    ps.clear();

    return XML_SUCCESS;
}

#endif
