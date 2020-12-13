#include "parser.hpp"

void Parser::addTag(const char* tag, std::shared_ptr<rt3::ParamSet> ps) {
    std::unique_ptr<bool[]> u_ptr(new bool[1]);
    u_ptr[0] = true;
    ps->add<bool>(tag, std::move(u_ptr), 1);
}

bool Parser::addBoolAttr(XMLElement* pE, const char* tag, std::shared_ptr<rt3::ParamSet> ps) {
    bool val = ParserTags::PARSER_DEFAULT_INT;
    auto xmlResult = pElement->QueryBoolAttribute(tag, &val);
    if (xmlResult != XML_SUCCESS) { return val; }
    std::unique_ptr<bool[]> u_ptr(new bool[1]);
    u_ptr[0] = val;
    ps->add<bool>(tag, std::move(u_ptr), 1);
    return val;
}

std::string Parser::addStrAttr(XMLElement* pE, const char* tag, std::shared_ptr<rt3::ParamSet> ps) {
    const char* str = ParserTags::PARSER_DEFAULT_STR;
    auto xmlResult = pElement->QueryStringAttribute(tag, &str);
    if (xmlResult != XML_SUCCESS) { return ""; } // value not found
    std::unique_ptr<std::string[]> u_ptr(new std::string[1]);
    u_ptr[0] = str;
    ps->add<std::string>(tag, std::move(u_ptr), 1);
    return str;
}

int Parser::addIntAttr(XMLElement* pE, const char* tag, std::shared_ptr<rt3::ParamSet> ps) {
    int val = ParserTags::PARSER_DEFAULT_INT;
    auto xmlResult = pElement->QueryIntAttribute(tag, &val);
    if (xmlResult != XML_SUCCESS) { return val; }
    std::unique_ptr<int[]> u_ptr(new int[1]);
    u_ptr[0] = val;
    ps->add<int>(tag, std::move(u_ptr), 1);
    return val;
}

float Parser::addFloatAttr(XMLElement* pE, const char* tag, std::shared_ptr<rt3::ParamSet> ps) {
    float val = ParserTags::PARSER_DEFAULT_FLOAT;
    auto xmlResult = pElement->QueryFloatAttribute(tag, &val);
    if (xmlResult != XML_SUCCESS) { return val; }
    std::unique_ptr<float[]> u_ptr(new float[1]);
    u_ptr[0] = val;
    ps->add<float>(tag, std::move(u_ptr), 1);
    return val;
}

void Parser::parse_film(XMLElement* pE) {
    ParamSet_ptr ps = std::make_shared<rt3::ParamSet>();

    addStrAttr(pElement, ParserTags::FILM_TYPE, ps);
    addIntAttr(pElement, ParserTags::FILM_X_RES, ps);
    addIntAttr(pElement, ParserTags::FILM_Y_RES, ps);
    addStrAttr(pElement, ParserTags::FILM_FILENAME, ps);
    addStrAttr(pElement, ParserTags::FILM_IMG_TYPE, ps);
    addStrAttr(pElement, ParserTags::FILM_CROP_WINDOW, ps);
    addStrAttr(pElement, ParserTags::FILM_GAMMA_CORRECTED, ps);

    // ps_map.insert(PS_map_pair(ParserTags::FILM, std::move(ps)));
    ps_map[ParserTags::FILM] = std::move(ps);
    // fname=ps_map[ParserTags::FILM]->find_one<string>(ParserTags::FILM_FILENAME, "");
    // return;
}

void Parser::parse_camera(XMLElement* pE) {
    ParamSet_ptr ps = std::make_shared<rt3::ParamSet>();

    addStrAttr(pElement, ParserTags::CAMERA_TYPE, ps);
    addStrAttr(pElement, ParserTags::CAMERA_SCREEN_WINDOW, ps);
    addFloatAttr(pElement, ParserTags::CAMERA_FOVY, ps);

    // ps_map.insert(PS_map_pair(ParserTags::CAMERA, ps));
    ps_map[ParserTags::CAMERA] = std::move(ps);
}

void Parser::parse_background(XMLElement* pE) {
    ParamSet_ptr ps = std::make_shared<rt3::ParamSet>();

    addStrAttr(pElement, ParserTags::BACKGROUND_TYPE, ps);
    addStrAttr(pElement, ParserTags::BACKGROUND_MAPPING, ps);
    addStrAttr(pElement, ParserTags::BACKGROUND_COLOR, ps);
    addStrAttr(pElement, ParserTags::BACKGROUND_BL, ps);
    addStrAttr(pElement, ParserTags::BACKGROUND_TL, ps);
    addStrAttr(pElement, ParserTags::BACKGROUND_TR, ps);
    addStrAttr(pElement, ParserTags::BACKGROUND_BR, ps);

    // ps_map.insert(PS_map_pair(ParserTags::BACKGROUND, ps));
    ps_map[ParserTags::BACKGROUND] = std::move(ps);

}

// NEW lookat ps
void Parser::parse_lookat(XMLElement* pE) {
    ParamSet_ptr ps = std::make_shared<rt3::ParamSet>();

    addStrAttr(pElement, ParserTags::LOOKAT_LOOK_AT, ps);
    addStrAttr(pElement, ParserTags::LOOKAT_LOOK_FROM, ps);
    addStrAttr(pElement, ParserTags::LOOKAT_UP, ps);

    // ps_map.insert(PS_map_pair(ParserTags::LOOKAT, ps));
    ps_map[ParserTags::LOOKAT] = std::move(ps);

}

void Parser::parse_integrator(XMLElement* pE) {
    ParamSet_ptr ps = std::make_shared<rt3::ParamSet>();

    std::string type = addStrAttr(pElement, ParserTags::INTEGRATOR_TYPE, ps);
    if (type.compare(ParserTags::INTEGRATOR_TYPE_DEPTH_MAP) == 0) {
        float f = addFloatAttr(pElement, ParserTags::INTEGRATOR_DEPTH_MAP_ZMIN, ps);
        f = addFloatAttr(pElement, ParserTags::INTEGRATOR_DEPTH_MAP_ZMAX, ps);
        string s = addStrAttr(pElement, ParserTags::INTEGRATOR_DEPTH_MAP_NEAR_COLOR, ps);
        s = addStrAttr(pElement, ParserTags::INTEGRATOR_DEPTH_MAP_FAR_COLOR, ps);
    }
    else if (type.compare(ParserTags::INTEGRATOR_TYPE_BLINN_PHONG) == 0) {
        addIntAttr(pElement, ParserTags::INTEGRATOR_BLINN_PHONG_DEPTH, ps);
    }

    // ps_map.insert(PS_map_pair(ParserTags::INTEGRATOR, ps));
    ps_map[ParserTags::INTEGRATOR] = std::move(ps);
}

void Parser::parse_material(XMLElement* pE, ParamSet_ptr& ps) {
    // ParamSet_ptr ps = std::make_shared<rt3::ParamSet>();
    ps = std::make_shared<rt3::ParamSet>();

    addStrAttr(pElement, ParserTags::MATERIAL_TYPE, ps);
    addStrAttr(pElement, ParserTags::MATERIAL_COLOR, ps);

    // ps_map.insert(PS_map_pair(ParserTags::MATERIAL, ps));
}

void Parser::parse_named_material(XMLElement* pE, ParamSet_ptr& ps) {
    // ParamSet_ptr ps = std::make_shared<rt3::ParamSet>();
    ps = std::make_shared<rt3::ParamSet>();

    addStrAttr(pElement, ParserTags::MATERIAL_TYPE, ps);
    addStrAttr(pElement, ParserTags::MATERIAL_BLINN_NAME, ps);
    addStrAttr(pElement, ParserTags::MATERIAL_BLINN_AMBIENT, ps);
    addStrAttr(pElement, ParserTags::MATERIAL_BLINN_DIFFUSE, ps);
    addStrAttr(pElement, ParserTags::MATERIAL_BLINN_SPECULAR, ps);
    addStrAttr(pElement, ParserTags::MATERIAL_BLINN_MIRROR, ps);
    addFloatAttr(pElement, ParserTags::MATERIAL_BLINN_GLOSSINESS, ps);

    // ps_map.insert(PS_map_pair(ParserTags::MATERIAL, ps));
}



void Parser::parse_sphere(XMLElement* pE, ParamSet_ptr& ps) {
    // ParamSet_ptr ps = std::make_shared<rt3::ParamSet>();
    ps = std::make_shared<rt3::ParamSet>();

    addTag(ParserTags::OBJECT_SPHERE, ps);
    addFloatAttr(pElement, ParserTags::OBJECT_RADIUS, ps);
    addStrAttr(pElement, ParserTags::OBJECT_CENTER, ps);

    // ps_map.insert(PS_map_pair(ParserTags::LOOKAT, ps));
}

void Parser::parse_light(XMLElement* pE, ParamSet_ptr& ps) {
    // ParamSet_ptr ps = std::make_shared<rt3::ParamSet>();
    ps = std::make_shared<rt3::ParamSet>();

    addStrAttr(pElement, ParserTags::LIGHT_TYPE, ps);
    addStrAttr(pElement, ParserTags::LIGHT_L, ps);
    addStrAttr(pElement, ParserTags::LIGHT_I, ps);
    addStrAttr(pElement, ParserTags::LIGHT_SCALE, ps);
    addStrAttr(pElement, ParserTags::LIGHT_FROM, ps);
    addStrAttr(pElement, ParserTags::LIGHT_TO, ps);
    addIntAttr(pElement, ParserTags::LIGHT_SPOT_CUTOFF, ps);
    addIntAttr(pElement, ParserTags::LIGHT_SPOT_FALLOFF, ps);

    // ps_map.insert(PS_map_pair(ParserTags::MATERIAL, ps));
}

void Parser::parse_object_identity(XMLElement* pE, ParamSet_ptr& ps) {
    // ParamSet_ptr ps = std::make_shared<rt3::ParamSet>();
    ps = std::make_shared<rt3::ParamSet>();

    // named material
    string m = addStrAttr(pElement, ParserTags::OBJECT_NAMED_MATERIAL_NAME, ps);

    // translate
    pElement = pElement->NextSiblingElement();
    if (strcmp(pElement->Name(), ParserTags::OBJECT_TRANSLATE) == 0) {
        string translate = addStrAttr(pElement, ParserTags::OBJECT_TRANSLATE_VALUE, ps);

        pElement = pElement->NextSiblingElement(ParserTags::OBJECT);
        addFloatAttr(pElement, ParserTags::OBJECT_RADIUS, ps);
    }
    else if (strcmp(pElement->Name(), ParserTags::OBJECT) == 0) {
        string t = addStrAttr(pElement, ParserTags::OBJECT_TYPE, ps);
        if (t.compare(ParserTags::OBJECT_TYPE_TRIANGLEMESH) == 0) {
            addIntAttr(pElement, ParserTags::OBJECT_TMESH_NTRIANGLES, ps);
            addStrAttr(pElement, ParserTags::OBJECT_TMESH_VERTICES, ps);
            addStrAttr(pElement, ParserTags::OBJECT_TMESH_INDICES, ps);
            addStrAttr(pElement, ParserTags::OBJECT_TMESH_NORMALS, ps);
            addBoolAttr(pElement, ParserTags::OBJECT_TMESH_RVO, ps);
            addBoolAttr(pElement, ParserTags::OBJECT_TMESH_BCULL, ps);
        }
    }

}

int Parser::parse_include() {
    const char* filenameInc = ParserTags::PARSER_DEFAULT_STR;
    auto xmlResult = pElement->QueryStringAttribute(ParserTags::INCLUDE_FILENAME, &filenameInc);
    if (xmlResult != XML_SUCCESS) { return XML_ERROR_PARSING_ATTRIBUTE; } // value not found

    XMLDocument subdoc;
    XMLNode* pRootInc;
    XMLElement* newElement;
    XMLError eResultInc = subdoc.LoadFile(filenameInc);
    XMLCheckResult(eResultInc);

    pRootInc = subdoc.FirstChild();
    if (pRootInc == nullptr) return XML_ERROR_FILE_READ_ERROR;

    XMLNode* copyNode;
    XMLElement* nodeInsertAt;
    pRootInc = pRootInc->FirstChildElement();
    nodeInsertAt = pElement;

    while (pRootInc != nullptr) {
        copyNode = pRootInc->ShallowClone(xmlDoc);
        newElement = copyNode->ToElement();
        // std::cout << newElement->Name() << " copying...\n";
        nodeInsertAt = xmlDoc->InsertAfterChild(nodeInsertAt, newElement)->ToElement();
        pRootInc = pRootInc->NextSiblingElement();
    }

    return 0;
}


// TODO(bnatalha): check if firstChildElement is RT3
int Parser::extractData(rt3::API& api)
{
    xmlDoc = new XMLDocument();
    XMLError eResult = xmlDoc->LoadFile(filename.c_str());
    XMLCheckResult(eResult);

    pRoot = xmlDoc->FirstChild();
    if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

    pElement = pRoot->FirstChildElement();

    // std::forward_list<std::pair<ParamSet_ptr, ParamSet_ptr>> ps_gprim_list = std::forward_list<std::pair<ParamSet_ptr, ParamSet_ptr>>();
    std::forward_list<ParamSet_ptr> ps_lights = std::forward_list<ParamSet_ptr>();
    std::forward_list<ParamSet_ptr> ps_materials = std::forward_list<ParamSet_ptr>();
    std::forward_list<ParamSet_ptr> ps_objects = std::forward_list<ParamSet_ptr>();

    while (pElement != nullptr) {
        std::cout << "Element: " << pElement->Name() << "\r";
        std::cout.flush();


        if (strcmp(pElement->Name(), ParserTags::FILM) == 0) {
            parse_film(pElement);
        }
        else if (strcmp(pElement->Name(), ParserTags::CAMERA) == 0) {
            parse_camera(pElement);
        }
        else if (strcmp(pElement->Name(), ParserTags::LOOKAT) == 0) {
            parse_lookat(pElement);
        }
        else if (strcmp(pElement->Name(), ParserTags::INTEGRATOR) == 0) {
            parse_integrator(pElement);
        }
        else if (strcmp(pElement->Name(), ParserTags::INCLUDE) == 0) {
            parse_include();
        }
        else if (strcmp(pElement->Name(), ParserTags::SCENE_WORLD_BEGIN) == 0) {
            pElement = pElement->NextSiblingElement();

            while (pElement != nullptr && strcmp(pElement->Name(), ParserTags::SCENE_WORLD_END) != 0) {
                // BACKGROUND
                ParamSet_ptr ps;
                // ParamSet_ptr ps = std::make_shared<rt3::ParamSet>();
                if (strcmp(pElement->Name(), ParserTags::BACKGROUND) == 0) {
                    parse_background(pElement);
                    // pElement = pElement->NextSiblingElement();
                }
                else if (strcmp(pElement->Name(), ParserTags::MAKE_NAMED_MATERIAL) == 0) {
                    parse_named_material(pElement, ps);
                    ps_materials.push_front(ps);
                }
                else if (strcmp(pElement->Name(), ParserTags::LIGHT) == 0) {
                    parse_light(pElement, ps);
                    ps_lights.push_front(ps);
                }
                else if (strcmp(pElement->Name(), ParserTags::OBJECT_NAMED_MATERIAL) == 0) {
                    parse_object_identity(pElement, ps);
                    ps_objects.push_front(ps);
                }
                else if (strcmp(pElement->Name(), ParserTags::OBJECT_IDENTITY) == 0) {
                    // TODO ?
                }
                else if (strcmp(pElement->Name(), ParserTags::INCLUDE) == 0) {
                    parse_include();
                }

                pElement = pElement->NextSiblingElement();
            }
        }
        if (strcmp(pElement->Name(), ParserTags::SCENE_WORLD_END) == 0
            || strcmp(pElement->Name(), ParserTags::RENDER_AGAIN) == 0) {
            std::cout << std::endl;
            // api.run(ps_map, ps_gprim_list);
            api.run(ps_map,
                ps_objects,
                ps_lights,
                ps_materials);

            ps_objects.clear();
            ps_lights.clear();
            ps_materials.clear();
        }
        pElement = pElement->NextSiblingElement();


    }
    delete xmlDoc;
    return XML_SUCCESS;
}