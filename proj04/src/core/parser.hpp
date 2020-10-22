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
#include <utility>
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

typedef std::shared_ptr<rt3::ParamSet> ParamSet_ptr;


class Parser
{
private:
    const std::string filename;
    XMLDocument xmlDoc;
    XMLNode* pRoot;
    XMLElement* pElement;

    std::shared_ptr<rt3::ParamSet> ps_film;
    std::shared_ptr<rt3::ParamSet> ps_camera;
    std::shared_ptr<rt3::ParamSet> ps_lookat;
    std::shared_ptr<rt3::ParamSet> ps_background;

public:
    Parser() {}
    Parser(std::string filename) : filename(filename) {}
    ~Parser() {}

    void parse_film(XMLElement* pE);
    void parse_camera(XMLElement* pE);
    void parse_lookat(XMLElement* pE);
    void parse_background(XMLElement* pE);
    void parse_material(XMLElement* pE, ParamSet_ptr& ps);
    void parse_sphere(XMLElement* pE, ParamSet_ptr& ps);
    int extractData(rt3::API& api);

    inline void addTag(const char* tag, std::shared_ptr<rt3::ParamSet> ps) {
        std::unique_ptr<bool[]> u_ptr(new bool[1]);
        u_ptr[0] = true;
        ps->add<bool>(tag, std::move(u_ptr), 1);
    }

    inline std::string addStrAttr(XMLElement* pE, const char* tag, std::shared_ptr<rt3::ParamSet> ps) {
        const char* str = ParserTags::PARSER_DEFAULT_STR;
        auto xmlResult = pElement->QueryStringAttribute(tag, &str);
        if (xmlResult != XML_SUCCESS) { return ""; } // value not found
        std::unique_ptr<std::string[]> u_ptr(new std::string[1]);
        u_ptr[0] = str;
        ps->add<std::string>(tag, std::move(u_ptr), 1);
        return str;
    }

    inline int addIntAttr(XMLElement* pE, const char* tag, std::shared_ptr<rt3::ParamSet> ps) {
        int val = ParserTags::PARSER_DEFAULT_INT;
        auto xmlResult = pElement->QueryIntAttribute(tag, &val);
        if (xmlResult != XML_SUCCESS) { return val; }
        std::unique_ptr<int[]> u_ptr(new int[1]);
        u_ptr[0] = val;
        ps->add<int>(tag, std::move(u_ptr), 1);
        return val;
    }

    inline float addFloatAttr(XMLElement* pE, const char* tag, std::shared_ptr<rt3::ParamSet> ps) {
        float val = ParserTags::PARSER_DEFAULT_FLOAT;
        auto xmlResult = pElement->QueryFloatAttribute(tag, &val);
        if (xmlResult != XML_SUCCESS) { return val; }
        std::unique_ptr<float[]> u_ptr(new float[1]);
        u_ptr[0] = val;
        ps->add<float>(tag, std::move(u_ptr), 1);
        return val;
    }
};

void Parser::parse_film(XMLElement* pE) {
    ps_film = std::make_shared<rt3::ParamSet>();

    addStrAttr(pElement, ParserTags::FILM_TYPE, ps_film);
    addIntAttr(pElement, ParserTags::FILM_X_RES, ps_film);
    addIntAttr(pElement, ParserTags::FILM_Y_RES, ps_film);
    addStrAttr(pElement, ParserTags::FILM_FILENAME, ps_film);
    addStrAttr(pElement, ParserTags::FILM_IMG_TYPE, ps_film);
    addStrAttr(pElement, ParserTags::FILM_CROP_WINDOW, ps_film);
    addStrAttr(pElement, ParserTags::FILM_GAMMA_CORRECTED, ps_film);
}

void Parser::parse_camera(XMLElement* pE) {
    ps_camera = std::make_shared<rt3::ParamSet>();

    addStrAttr(pElement, ParserTags::CAMERA_TYPE, ps_camera);
    addStrAttr(pElement, ParserTags::CAMERA_SCREEN_WINDOW, ps_camera);
    addIntAttr(pElement, ParserTags::CAMERA_FOVY, ps_camera);
}

void Parser::parse_background(XMLElement* pE) {
    ps_background = std::make_shared<rt3::ParamSet>();

    addStrAttr(pElement, ParserTags::BACKGROUND_TYPE, ps_background);
    addStrAttr(pElement, ParserTags::BACKGROUND_MAPPING, ps_background);
    addStrAttr(pElement, ParserTags::BACKGROUND_COLOR, ps_background);
    addStrAttr(pElement, ParserTags::BACKGROUND_BL, ps_background);
    addStrAttr(pElement, ParserTags::BACKGROUND_TL, ps_background);
    addStrAttr(pElement, ParserTags::BACKGROUND_TR, ps_background);
    addStrAttr(pElement, ParserTags::BACKGROUND_BR, ps_background);
}

// NEW lookat ps
void Parser::parse_lookat(XMLElement* pE) {
    ps_lookat = std::make_shared<rt3::ParamSet>();

    addTag(ParserTags::LOOKAT, ps_lookat);
    addStrAttr(pElement, ParserTags::LOOKAT_LOOK_AT, ps_lookat);
    addStrAttr(pElement, ParserTags::LOOKAT_LOOK_FROM, ps_lookat);
    addStrAttr(pElement, ParserTags::LOOKAT_UP, ps_lookat);
}

void Parser::parse_material(XMLElement* pE, ParamSet_ptr& ps) {
    addStrAttr(pElement, ParserTags::MATERIAL_TYPE, ps);
    addStrAttr(pElement, ParserTags::MATERIAL_COLOR, ps);
}

void Parser::parse_sphere(XMLElement* pE, ParamSet_ptr& ps) {
    addTag(ParserTags::OBJECT_SPHERE, ps);
    // float radius = addFloatAttr(pElement, ParserTags::OBJECT_RADIUS, ps_obj);
    // std::string center = addStrAttr(pElement, ParserTags::OBJECT_CENTER, ps_obj);
    addFloatAttr(pElement, ParserTags::OBJECT_RADIUS, ps);
    addStrAttr(pElement, ParserTags::OBJECT_CENTER, ps);
    // std::cout << "read " << type << " with radius " << radius << "and center (" << center << ")\n";
}


// TODO(bnatalha): list/map of paramsets
// TODO(bnatalha): check if firstChildElement is RT3
int Parser::extractData(rt3::API& api)
{

    XMLError eResult = xmlDoc.LoadFile(filename.c_str());
    XMLCheckResult(eResult);

    pRoot = xmlDoc.FirstChild();
    if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

    pElement = pRoot->FirstChildElement();

    rt3::ParamSet ps_camera;


    while (pElement != nullptr) {
        if (pElement->Name() == ParserTags::FILM) {
            parse_film(pElement);
        }
        else if (pElement->Name() == ParserTags::CAMERA) {
            parse_camera(pElement);
        }
        else if (pElement->Name() == ParserTags::LOOKAT) {
            parse_lookat(pElement);
        }
        else if (pElement->Name() == ParserTags::INCLUDE) {
            const char* filenameInc = ParserTags::PARSER_DEFAULT_STR;
            auto xmlResult = pElement->QueryStringAttribute(ParserTags::INCLUDE_FILENAME, &filenameInc);
            if (xmlResult != XML_SUCCESS) { return XML_ERROR_PARSING_ATTRIBUTE; } // value not found

            XMLDocument xmlDocInc;
            XMLNode* pRootInc;
            XMLElement* pElementInc;
            XMLError eResultInc = xmlDoc.LoadFile(filenameInc);
            XMLCheckResult(eResult);

            pRootInc = xmlDocInc.FirstChild();
            if (pRootInc == nullptr) return XML_ERROR_FILE_READ_ERROR;

            pElementInc = pRootInc->FirstChildElement();
            while (pElementInc != nullptr) {
                xmlDoc.InsertAfterChild(pElement, pElementInc);
            }
        }
        else if (pElement->Name() == ParserTags::SCENE_WORLD_BEGIN) {
            pElement->NextSiblingElement();

            // BACKGROUND
            rt3::ParamSet ps_bg;
            if (pElement->Name() == ParserTags::BACKGROUND) {
                parse_background(pElement);
            }
            else {
                std::cerr << "> [E]! Parser: Missing Backgroud\n";
            }

            std::forward_list<std::pair<ParamSet_ptr, ParamSet_ptr>> ps_gprim_list = std::forward_list<std::pair<ParamSet_ptr, ParamSet_ptr>>();

            // Como sei que esse material é pra esse object?
            while (pElement != nullptr || pElement->Name() != ParserTags::SCENE_WORLD_END) {
                ParamSet_ptr ps_material = std::make_shared<rt3::ParamSet>();
                if (pElement->Name() == ParserTags::MATERIAL) {
                    parse_material(pElement, ps_material);
                }
                else {
                    // criar Material default flat red
                    // <material type="flat" color="255 0 0" />
                }

                pElement->NextSibling();
                while (pElement != nullptr && pElement->Name() == ParserTags::OBJECT)
                {
                    ParamSet_ptr ps_obj = std::make_shared<rt3::ParamSet>();
                    std::string type = addStrAttr(pElement, ParserTags::OBJECT_TYPE, ps_obj);
                    if (type.compare(ParserTags::OBJECT_SPHERE) == 0) {
                        parse_sphere(pElement, ps_obj);
                    }
                    std::pair<ParamSet_ptr, ParamSet_ptr> gprim = std::pair<ParamSet_ptr, ParamSet_ptr>(ps_obj, ps_material);
                    ps_gprim_list.push_front(gprim);
                    pElement = pElement->NextSiblingElement();
                }
            }

        }

        return XML_SUCCESS;
    }

#endif
