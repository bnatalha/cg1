#ifndef API_HPP
#define API_HPP

#include <memory>
#include <sstream>
#include <string>

#include "header.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "paramset.hpp"

namespace rt3 {

    using std::string;

    class API
    {

    public:
        // static std::shared_ptr<Camera> camera;
        // static std::shared_ptr<Scene> scene;
        std::shared_ptr<Camera> m_camera = nullptr;
        std::shared_ptr<Scene> m_scene = nullptr;

        // Constructors & Destructors

        API(){}
        ~API(){}

        //  ============================= Camera ============================

        void camera(const ParamSet & ps) {
            string t = ps.find_one<std::string>("type", "default");
            m_camera = create_camera(t);
        }

        std::shared_ptr<Camera> create_camera(string type) {
            return std::make_shared<Camera>(type);
        }

        void camera_film(const ParamSet & ps) {
            std::stringstream sstr;

            string type = ps.find_one<std::string>("type", "default");
            string filename = ps.find_one<std::string>("filename", "test_img.png");
            string img_type = ps.find_one<std::string>("img_type", "PNG");
            int y_res = ps.find_one<int>("y_res", 100);
            int x_res = ps.find_one<int>("x_res", 200);

            m_camera->film = Film(type, y_res, x_res, filename, img_type);
        }

        // ========================== Scene =================================

        string sample_corner_color(const char* corner_name, bool & flag, const ParamSet &ps) {
            string foundCorner = ps.find_one<string>(corner_name, "not_provided");
            string corner = DEFAULT_COLOR;
            if(foundCorner.compare("not_provided") != 0) {
                corner = foundCorner; 
                flag = true;
            }
            return corner;
        }

        void scene(const ParamSet & ps) {
            string t = ps.find_one<string>("type", "default");
            string mp = ps.find_one<string>("mapping", DEFAULT_MAPPING);
            string color = ps.find_one<string>("color", DEFAULT_COLOR);

            bool providedCorners = false;

            // string bl = ps.find_one<string>("bl", "not_provided");
            // string tl = ps.find_one<string>("tl", "not_provided");
            // string tr = ps.find_one<string>("tr", "not_provided");
            // string br = ps.find_one<string>("br", "not_provided");

            string bl = sample_corner_color("bl", providedCorners, ps);
            string tl = sample_corner_color("tl", providedCorners, ps);
            string tr = sample_corner_color("tr", providedCorners, ps);
            string br = sample_corner_color("br", providedCorners, ps);

            Background bg(providedCorners, t, mp, color, bl, tl, tr, br);

            m_scene = create_scene(bg);
        }

        std::shared_ptr<Scene> create_scene(Background &bg) {
            return std::make_shared<Scene>(bg);
        }

        // ================================== Aux ==================================
        inline void print(){
            m_camera->print();
            m_scene->print();
        }

        void RT() {
            auto w = m_camera->film.width;
            auto h = m_camera->film.height;
            // for ( int j = h-1 ; j >= 0 ; j-- ) {
            for ( int j = 0 ; j < h; j++ ) {
                for( int i = 0 ; i < w ; i++ ) {
                    auto color = m_scene->background.sample( float(i)/float(w), float(j)/float(h) ); // get background color.
                    m_camera->film.add( Point2(i,j), color ); // set image buffer at position (i,j), accordingly.
                }
            }
        }

        void save(){
            m_camera->film.write_image();
        }
    };
}

#endif