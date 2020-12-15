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
#include <unordered_map>
#include <utility>
#include <string.h>
#include "external/tinyxml2.hpp"

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
    XMLDocument* xmlDoc;
    XMLNode* pRoot;
    XMLElement* pElement;

    std::unordered_map<const char*, ParamSet_ptr> ps_map = std::unordered_map<const char*, ParamSet_ptr>();

public:
    Parser() {}
    Parser(std::string filename) : filename(filename) {}
    ~Parser() {}

    void parse_film(XMLElement* pE);
    void parse_camera(XMLElement* pE);
    void parse_lookat(XMLElement* pE);
    void parse_integrator(XMLElement* pE);
    void parse_background(XMLElement* pE);
    void parse_light(XMLElement* pE, ParamSet_ptr& ps);
    void parse_material(XMLElement* pE, ParamSet_ptr& ps);
    void parse_named_material(XMLElement* pE, ParamSet_ptr& ps);
    void parse_object_identity(XMLElement* pE, ParamSet_ptr& ps);
    void parse_sphere(XMLElement* pE, ParamSet_ptr& ps);
    
    int parse_include();

    int extractData(rt3::API& api);

    void addTag(const char* tag, std::shared_ptr<rt3::ParamSet> ps);
    bool addBoolAttr(XMLElement* pE, const char* tag, std::shared_ptr<rt3::ParamSet> ps);
    std::string addStrAttr(XMLElement* pE, const char* tag, std::shared_ptr<rt3::ParamSet> ps);
    int addIntAttr(XMLElement* pE, const char* tag, std::shared_ptr<rt3::ParamSet> ps) ;
    float addFloatAttr(XMLElement* pE, const char* tag, std::shared_ptr<rt3::ParamSet> ps);
};



#endif
