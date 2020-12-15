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
#include "integrator.hpp"
#include "light.hpp"
#include "integrator/flat_integrator.hpp"
#include "integrator/normal_map_integrator.hpp"
#include "integrator/depth_map_integrator.hpp"
#include "integrator/blinn_phong_integrator.hpp"
#include "primitive/geometric_primitive.hpp"
#include "primitive/prim_list.hpp"
#include "primitive/flat_material.hpp"
#include "primitive/material.hpp"
#include "primitive/BVHAccel.hpp"

// #include "primitive/blinn_phong_material.hpp"
// #include "light/point_light.hpp"

namespace rt3 {

    using std::string;

    class API
    {

    public:
        std::shared_ptr<Scene> m_scene = nullptr;
        std::shared_ptr<Integrator> m_integrator = nullptr;
        bool m_verbose;

        API() : m_verbose(false) {}
        API(bool verbose) : m_verbose(verbose) {}
        ~API() {}

        std::shared_ptr<Camera> camera(ParamSet_ptr& ps_camera, ParamSet_ptr& ps_film, ParamSet_ptr& ps_lookat);

        // ========================== Scene =================================

        string sample_corner_color(const char* corner_name, bool& flag, ParamSet_ptr& ps);

        // TODO(bnatalha): function for background parsing only
        void scene(ParamSet_ptr& ps_bg, std::forward_list<std::pair<ParamSet_ptr, ParamSet_ptr>>& primitives);
        // void scene(ParamSet_ptr& ps_bg, std::forward_list<ParamSet_ptr>& objects, std::forward_list<ParamSet_ptr>& lights, std::forward_list<ParamSet_ptr>& materials);
        void scene(ParamSet_ptr& ps_bg, ParamSet_ptr& ps_acc, std::forward_list<ParamSet_ptr>& ps_objects, std::forward_list<ParamSet_ptr>& ps_lights, std::forward_list<ParamSet_ptr>& ps_materials);

        void integrator(ParamSet_ptr& ps_it, std::shared_ptr<Camera> camera);

        // ================================== Aux ==================================
        void print();

        // ============================ Main functions ================================

        void render();

        void save();

        void run(std::unordered_map<const char*, ParamSet_ptr>& paramsets,
            std::forward_list<std::pair<ParamSet_ptr, ParamSet_ptr>>& primitives);

        void run(std::unordered_map<const char*, ParamSet_ptr>& paramsets,
            std::forward_list<ParamSet_ptr>& objects,
            std::forward_list<ParamSet_ptr>& lights,
            std::forward_list<ParamSet_ptr>& materials
        );
    };
}

#endif