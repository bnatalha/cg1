#ifndef API_HPP
#define API_HPP

#include <memory>
#include <sstream>
#include <string>

#include "camera.hpp"
// #include "Film.hpp"
#include "scene.hpp"

#include "paramset.hpp"

namespace rt3 {

    /**
     * Is responsible for returning a color each time the primary ray misses any object in the scene (i.e. hits nothing).
     * */
    class API
    {

    public:
        // static std::shared_ptr<Camera> camera;
        // static std::shared_ptr<Scene> scene;
        std::shared_ptr<Camera> m_camera = nullptr;
        std::shared_ptr<Scene> m_scene = nullptr;

        // Constructors & Destructors

        API(){
            // camera = std::make_shared<Camera>();
            // scene = std::make_shared<Scene>();
        }
        ~API(){}

        // Camera


        void camera(const ParamSet & ps) {
            string t = ps.find_one("type", "default");
            m_camera = create_camera(t);
        }

        std::shared_ptr<Camera> create_camera(string type) {
            return std::make_shared<Camera>(type);
        }
        
        void camera_film(const ParamSet & ps) {
            std::stringstream sstr;

            string type = ps.find_one("type", "default");
            string filename = ps.find_one("filename", "test_img.png");
            string img_type = ps.find_one("img_type", "PNG");

            sstr << ps.find_one("x_res", "100") << ps.find_one("y_res", "100");
            int x_res, y_res;
            sstr >> x_res >> y_res; // checar se não está trocando a ordem
            
            m_camera->film = Film(type, y_res, x_res, filename, img_type);
        }


        // Scene
        void scene(const ParamSet & ps) {
            // string t = ps.find_one("type", "default");
            // camera = create_camera(t);
        }

        // std::shared_ptr<Camera> create_scene(/* args */) {
        //     return std::make_shared<Scene>(t);
        // }
        

        // Aux
        
        inline void print(){
            m_camera->print();
            // m_scene->print();
        }
        
    };
}


#endif