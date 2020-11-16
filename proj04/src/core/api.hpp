#ifndef API_HPP
#define API_HPP

#include <memory>
#include <sstream>
#include <string>
#include <forward_list>

#include "header.hpp"
#include "vector3.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "paramset.hpp"
#include "parser_tags.hpp"
#include "primitive.hpp"
// #include "parser.hpp"

namespace rt3 {

    using std::string;

    class API
    {

    public:
        std::shared_ptr<Camera> m_camera = nullptr;
        std::shared_ptr<Scene> m_scene = nullptr;
        bool m_verbose;

        API() : m_verbose(false) {}
        API(bool verbose) : m_verbose(verbose) {}
        ~API() {}

        //  ============================= Camera ============================


        // // TODO(bnatalha): implement 'crop_window' extraction
        // Film camera_film(const ParamSet& ps) {
        //     std::stringstream sstr;

        //     string type = ps.find_one<std::string>(ParserTags::FILM_TYPE, "default");
        //     string filename = ps.find_one<std::string>(ParserTags::FILM_FILENAME, "test_img.png");
        //     string img_type = ps.find_one<std::string>(ParserTags::FILM_IMG_TYPE, "PNG");
        //     int y_res = ps.find_one<int>(ParserTags::FILM_Y_RES, 100);
        //     int x_res = ps.find_one<int>(ParserTags::FILM_X_RES, 200);

        //     return Film(type, y_res, x_res, filename, img_type);
        // }

        void camera(ParamSet_ptr& ps_camera, ParamSet_ptr& ps_film, ParamSet_ptr& ps_lookat);

        // ========================== Scene =================================

        string sample_corner_color(const char* corner_name, bool& flag, const ParamSet& ps);

        // TODO(bnatalha): function for background parsing only
        void scene(const ParamSet& ps_bg, const std::forward_list<ParamSet>& ps_obj_list);

        // ================================== Aux ==================================
        void print();

        // ============================ Main functions ================================

        void render();

        void save() ;

        void run(std::unordered_map<const char*, ParamSet_ptr>& paramsets);
    };
}

#endif