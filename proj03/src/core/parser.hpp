#ifndef PARSER_HPP
#define PARSER_HPP

/**
 * Based on https://shilohjames.wordpress.com/2014/04/27/tinyxml2-tutorial/
 **/

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <forward_list>
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

    inline void addTag(const char* tag, rt3::ParamSet& ps) {
        std::unique_ptr<bool[]> u_ptr(new bool[1]);
        u_ptr[0] = true;
        ps.add<bool>(tag, std::move(u_ptr), 1);
    }

    inline std::string addStrAttr(XMLElement* pE, const char* tag, rt3::ParamSet& ps) {
        const char* str = ParserTags::PARSER_DEFAULT_STR;
        auto xmlResult = pElement->QueryStringAttribute(tag, &str);
        if (xmlResult != XML_SUCCESS) { return ""; } // value not found
        std::unique_ptr<std::string[]> u_ptr(new std::string[1]);
        u_ptr[0] = str;
        ps.add<std::string>(tag, std::move(u_ptr), 1);
        return str;
    }

    inline int addIntAttr(XMLElement* pE, const char* tag, rt3::ParamSet& ps) {
        int val = ParserTags::PARSER_DEFAULT_INT;
        auto xmlResult = pElement->QueryIntAttribute(tag, &val);
        if (xmlResult != XML_SUCCESS) { return val; }
        std::unique_ptr<int[]> u_ptr(new int[1]);
        u_ptr[0] = val;
        ps.add<int>(tag, std::move(u_ptr), 1);
        return val;
    }

    inline float addFloatAttr(XMLElement* pE, const char* tag, rt3::ParamSet& ps) {
        float val = ParserTags::PARSER_DEFAULT_FLOAT;
        auto xmlResult = pElement->QueryFloatAttribute(tag, &val);
        if (xmlResult != XML_SUCCESS) { return val; }
        std::unique_ptr<float[]> u_ptr(new float[1]);
        u_ptr[0] = val;
        ps.add<float>(tag, std::move(u_ptr), 1);
        return val;
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


    // setting film
    rt3::ParamSet ps_film;
    pElement = pRoot->FirstChildElement(ParserTags::FILM);

    addStrAttr(pElement, ParserTags::FILM_TYPE, ps_film);
    addIntAttr(pElement, ParserTags::FILM_X_RES, ps_film);
    addIntAttr(pElement, ParserTags::FILM_Y_RES, ps_film);
    addStrAttr(pElement, ParserTags::FILM_FILENAME, ps_film);
    addStrAttr(pElement, ParserTags::FILM_IMG_TYPE, ps_film);
    addStrAttr(pElement, ParserTags::FILM_CROP_WINDOW, ps_film);
    addStrAttr(pElement, ParserTags::FILM_GAMMA_CORRECTED, ps_film);

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

    api.camera(ps, ps_film);
    ps_film.clear();
    ps.clear();

    // setting scene
    rt3::ParamSet ps_bg;
    pElement = pRoot->FirstChildElement(ParserTags::BACKGROUND);

    addStrAttr(pElement, ParserTags::BACKGROUND_TYPE, ps_bg);
    addStrAttr(pElement, ParserTags::BACKGROUND_MAPPING, ps_bg);
    addStrAttr(pElement, ParserTags::BACKGROUND_COLOR, ps_bg);
    addStrAttr(pElement, ParserTags::BACKGROUND_BL, ps_bg);
    addStrAttr(pElement, ParserTags::BACKGROUND_TL, ps_bg);
    addStrAttr(pElement, ParserTags::BACKGROUND_TR, ps_bg);
    addStrAttr(pElement, ParserTags::BACKGROUND_BR, ps_bg);

    // getting objects
    std::forward_list<rt3::ParamSet> ps_obj_list = std::forward_list<rt3::ParamSet>();
    pElement = pRoot->FirstChildElement(ParserTags::OBJECT);
    while (pElement != nullptr) {
        rt3::ParamSet ps_obj;
        std::string type = addStrAttr(pElement, ParserTags::OBJECT_TYPE, ps_obj);
        if (type.compare(ParserTags::OBJECT_SPHERE) == 0) {
            addTag(ParserTags::OBJECT_SPHERE, ps_obj);
            // float radius = addFloatAttr(pElement, ParserTags::OBJECT_RADIUS, ps_obj);
            // std::string center = addStrAttr(pElement, ParserTags::OBJECT_CENTER, ps_obj);
            addFloatAttr(pElement, ParserTags::OBJECT_RADIUS, ps_obj);
            addStrAttr(pElement, ParserTags::OBJECT_CENTER, ps_obj);
            // std::cout << "read " << type << " with radius " << radius << "and center (" << center << ")\n";
        }
        ps_obj_list.push_front(ps_obj);

        pElement = pElement->NextSiblingElement(ParserTags::OBJECT);
    }



    api.scene(ps_bg, ps_obj_list);

    for (auto _ps : ps_obj_list) {
        _ps.clear();
    }
    ps_bg.clear();

    return XML_SUCCESS;
}

#endif
