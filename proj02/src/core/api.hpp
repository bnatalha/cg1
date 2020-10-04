#ifndef API_HPP
#define API_HPP

#include <memory>
#include <sstream>
#include <string>

#include "header.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "paramset.hpp"
#include "parser_tags.hpp"

namespace rt3 {

    using std::string;

    class API
    {

    public:
        std::shared_ptr<Camera> m_camera = nullptr;
        std::shared_ptr<Scene> m_scene = nullptr;
        bool m_verbose;

        // Constructors & Destructors

        API() : m_verbose(false) {}
        API(bool verbose) : m_verbose(verbose) {}
        ~API() {}

        //  ============================= Camera ============================

        void camera(const ParamSet& ps) {
            std::stringstream sstr;

            string type = ps.find_one<std::string>(ParserTags::CAMERA_TYPE, ParserTags::CAMERA_TYPE_ORTOGRAPHIC);
            if (type.compare(ParserTags::CAMERA_TYPE_PERSPECTIVE) == 0) {
                int fovy = ps.find_one<int>(ParserTags::CAMERA_FOVY, 30);
                m_camera = std::make_shared<PerspectiveCamera>(type, fovy);
            }
            else {  // ORTAGRAPHIC
                string screen_window = ps.find_one<std::string>(ParserTags::CAMERA_SCREEN_WINDOW, ParserTags::PARSER_DEFAULT_STR);
                if (screen_window.compare(ParserTags::PARSER_DEFAULT_STR) == 0) {
                    m_camera = std::make_shared<OrtographicCamera>(type);
                }
                else {
                    float l, r, b, t;
                    sstr << screen_window;
                    sstr >> l >> r >> b >> t;
                    m_camera = std::make_shared<OrtographicCamera>(type, l, r, b, t);
                }
            }

            // lookat
            string look_at;
            string look_from;
            string up;
            bool hasLookat = ps.find_one<bool>(ParserTags::LOOKAT, false);
            if (hasLookat) {
                Vector3 look_at = Vector3(ps.find_one<std::string>(ParserTags::LOOKAT_LOOK_AT, "0 0 0").c_str());
                Vector3 look_from = Vector3(ps.find_one<std::string>(ParserTags::LOOKAT_LOOK_FROM, "0 0 0").c_str());
                Vector3 vup = Vector3(ps.find_one<std::string>(ParserTags::LOOKAT_UP, "0 0 0").c_str());

                Vector3 gaze = look_at - look_from;
                Vector3 w = normalize(gaze);
                Vector3 u = normalize(cross(vup, w));
                Vector3 v = normalize(cross(w, u));

                m_camera->gaze = gaze;
                m_camera->_w = w;
                m_camera->_u = u;
                m_camera->_v = v;
                m_camera->e = look_from;

            }
        }

        // TODO(bnatalha): implement 'crop_window' extraction
        void camera_film(const ParamSet& ps) {
            std::stringstream sstr;

            string type = ps.find_one<std::string>(ParserTags::FILM_TYPE, "default");
            string filename = ps.find_one<std::string>(ParserTags::FILM_FILENAME, "test_img.png");
            string img_type = ps.find_one<std::string>(ParserTags::FILM_IMG_TYPE, "PNG");
            int y_res = ps.find_one<int>(ParserTags::FILM_Y_RES, 100);
            int x_res = ps.find_one<int>(ParserTags::FILM_X_RES, 200);

            m_camera->film = Film(type, y_res, x_res, filename, img_type);
        }

        // ========================== Scene =================================

        string sample_corner_color(const char* corner_name, bool& flag, const ParamSet& ps) {
            string foundCorner = ps.find_one<string>(corner_name, "not_provided");
            string corner = DEFAULT_COLOR;
            if (foundCorner.compare("not_provided") != 0) {
                corner = foundCorner;
                flag = true;
            }
            return corner;
        }

        // TODO(bnatalha): function for background parsing only
        void scene(const ParamSet& ps) {

            // BACKGROUND
            string t = ps.find_one<string>(ParserTags::BACKGROUND_TYPE, "default");
            string mp = ps.find_one<string>(ParserTags::BACKGROUND_MAPPING, DEFAULT_MAPPING);
            string color = ps.find_one<string>(ParserTags::BACKGROUND_COLOR, DEFAULT_COLOR);

            bool providedCorners = false;

            string bl = sample_corner_color(ParserTags::BACKGROUND_BL, providedCorners, ps);
            string tl = sample_corner_color(ParserTags::BACKGROUND_TL, providedCorners, ps);
            string tr = sample_corner_color(ParserTags::BACKGROUND_TR, providedCorners, ps);
            string br = sample_corner_color(ParserTags::BACKGROUND_BR, providedCorners, ps);

            Background bg(providedCorners, t, mp, color, bl, tl, tr, br);

            m_scene = create_scene(bg);
        }

        std::shared_ptr<Scene> create_scene(Background& bg) {
            return std::make_shared<Scene>(bg);
        }

        // ================================== Aux ==================================
        inline void print() {
            m_camera->print();
            m_scene->print();
        }

        // prints only if m_verbose == true
        inline void vprint(const char* msg) {
            if (m_verbose) {
                std::cout << msg;
            }
        }

        // ============================ Main functions ================================

        inline void RT() {
            auto w = m_camera->film.width;
            auto h = m_camera->film.height;
            // for ( int j = h-1 ; j >= 0 ; j-- ) {
            for (int j = 0; j < h; j++) {
                for (int i = 0; i < w; i++) {

                    Ray r1 = m_camera->generate_ray(float(i) / float(w), float(j) / float(h));

                    Ray r2 = m_camera->generate_ray(i, j);

                    // Print out the two rays, that must be the same (regardless of the method).

                    if (i % 100 == 0) {
                        std::cout << "Ray1: " << r1 << "\n";
                        std::cout << "Ray2: " << r2 << "\n" << std::endl;
                    }
                    // std::cout << "Point at t=2, ray(2) = " << r1(2.f) << std::endl;


                    // sample background
                    auto color = m_scene->background.sample(float(i) / float(w), float(j) / float(h)); // get background color.
                    m_camera->film.add(Point2(i, j), color); // set image buffer at position (i,j), accordingly.
                }
            }
        }

        inline void save() {
            m_camera->film.write_image();
        }
    };
}

#endif