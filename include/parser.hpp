#ifndef PARSER_HPP
#define PARSER_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <unordered_map>
#include <exception>
#include <iostream>
namespace pt = boost::property_tree;

#define PROGRAM_NAME "RT3"

struct world_tag
{
    std::string m_background;
};

class parser
{
private:
    world_tag m_world;
    std::unordered_map<std::string, std::string> m_camera;
    std::unordered_map<std::string, std::string> m_film;
public:
    parser(const std::string& filename);
    ~parser();
};

parser::parser(const std::string& filename)
{
    pt::ptree tree;
    std::ifstream ifs("./data/in/ex1.xml");
    pt::read_xml(ifs, tree);
    // m_world.m_background = tree.get(PROGRAM_NAME+".background")
    // m_camera.insert({type,tree.get(PROGRAM_NAME+".camera.xmlattr") });
    // std::cout << tree.get("RT3.camera").get_child("<xmlattr>")get("type").data();
    std::cout << tree.get<pt::ptree>("RT3.camera").get_child("<xmlattr>")get("type").data();
    // std::cout << tree.get<std::string>("RT3.camera").data();
    // std::cout << tree.get<std::string>("RT3.camera").data();
}

parser::~parser()
{
}


#endif