#ifndef API_HPP
#define API_HPP

#include <memory>
#include <sstream>
#include <string>
#include <forward_list>

#include "header.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "paramset.hpp"
#include "parser_tags.hpp"
#include "primitive.hpp"

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


        // TODO(bnatalha): implement 'crop_window' extraction
        Film camera_film(const ParamSet& ps) {
            std::stringstream sstr;

            string type = ps.find_one<std::string>(ParserTags::FILM_TYPE, "default");
            string filename = ps.find_one<std::string>(ParserTags::FILM_FILENAME, "test_img.png");
            string img_type = ps.find_one<std::string>(ParserTags::FILM_IMG_TYPE, "PNG");
            int y_res = ps.find_one<int>(ParserTags::FILM_Y_RES, 100);
            int x_res = ps.find_one<int>(ParserTags::FILM_X_RES, 200);

            return Film(type, y_res, x_res, filename, img_type);
        }

        void camera(const ParamSet& ps_camera, const ParamSet& ps_film) {
            std::stringstream sstr;

            // set camera film

            string type = ps_camera.find_one<std::string>(ParserTags::CAMERA_TYPE, ParserTags::CAMERA_TYPE_ORTOGRAPHIC);
            if (type.compare(ParserTags::CAMERA_TYPE_PERSPECTIVE) == 0) {
                int fovy = ps_camera.find_one<int>(ParserTags::CAMERA_FOVY, 30);
                m_camera = std::make_shared<PerspectiveCamera>(type, fovy);
                m_camera->film = camera_film(ps_film);
            }
            else {  // ORTAGRAPHIC
                m_camera = std::make_shared<OrtographicCamera>(type);
                string screen_window = ps_camera.find_one<std::string>(ParserTags::CAMERA_SCREEN_WINDOW, ParserTags::PARSER_DEFAULT_STR);
                if (screen_window.compare(ParserTags::PARSER_DEFAULT_STR) != 0) {
                    float l, r, b, t;
                    sstr << screen_window;
                    sstr >> l >> r >> b >> t;
                    m_camera->set_lrbt(l, r, b, t);
                }
                m_camera->film = camera_film(ps_film);
            }

            m_camera->set_lrbt();

            // lookat
            string look_at;
            string look_from;
            string up;
            bool hasLookat = ps_camera.find_one<bool>(ParserTags::LOOKAT, false);
            if (hasLookat) {
                Vector3 look_at = Vector3(ps_camera.find_one<std::string>(ParserTags::LOOKAT_LOOK_AT, "0 0 0").c_str());
                Vector3 look_from = Vector3(ps_camera.find_one<std::string>(ParserTags::LOOKAT_LOOK_FROM, "0 0 0").c_str());
                Vector3 vup = Vector3(ps_camera.find_one<std::string>(ParserTags::LOOKAT_UP, "0 0 0").c_str());

                Vector3 gaze = look_at - look_from;
                Vector3 w = normalize(gaze);
                Vector3 u = normalize(cross(vup, w));
                // Vector3 v = normalize(cross(u, w));
                Vector3 v = normalize(cross(w, u));

                m_camera->gaze = gaze;
                m_camera->_w = w;
                m_camera->_u = u;
                m_camera->_v = v;
                m_camera->e = look_from;

            }
        }

        // // TODO(bnatalha): implement 'crop_window' extraction
        // void camera_film(const ParamSet& ps) {
        //     std::stringstream sstr;

        //     string type = ps.find_one<std::string>(ParserTags::FILM_TYPE, "default");
        //     string filename = ps.find_one<std::string>(ParserTags::FILM_FILENAME, "test_img.png");
        //     string img_type = ps.find_one<std::string>(ParserTags::FILM_IMG_TYPE, "PNG");
        //     int y_res = ps.find_one<int>(ParserTags::FILM_Y_RES, 100);
        //     int x_res = ps.find_one<int>(ParserTags::FILM_X_RES, 200);

        //     m_camera->film = Film(type, y_res, x_res, filename, img_type);
        // }

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
        void scene(const ParamSet& ps_bg, const std::forward_list<ParamSet>& ps_obj_list) {

            // BACKGROUND
            string t = ps_bg.find_one<string>(ParserTags::BACKGROUND_TYPE, "default");
            string mp = ps_bg.find_one<string>(ParserTags::BACKGROUND_MAPPING, DEFAULT_MAPPING);
            string color = ps_bg.find_one<string>(ParserTags::BACKGROUND_COLOR, DEFAULT_COLOR);

            bool providedCorners = false;

            string bl = sample_corner_color(ParserTags::BACKGROUND_BL, providedCorners, ps_bg);
            string tl = sample_corner_color(ParserTags::BACKGROUND_TL, providedCorners, ps_bg);
            string tr = sample_corner_color(ParserTags::BACKGROUND_TR, providedCorners, ps_bg);
            string br = sample_corner_color(ParserTags::BACKGROUND_BR, providedCorners, ps_bg);

            Background bg(providedCorners, t, mp, color, bl, tl, tr, br);

            // Objects
            if (ps_obj_list.empty()) {
                m_scene = std::make_shared<Scene>(bg);
            }
            else {
                ObjectList primitives = ObjectList();
                for (ParamSet ps_obj : ps_obj_list) {
                    if (ps_obj.find_one<bool>(ParserTags::OBJECT_SPHERE, false)) {
                        float radius = ps_obj.find_one<float>(ParserTags::OBJECT_RADIUS, -23423.f);
                        Point3 center = Point3(ps_obj.find_one<std::string>(ParserTags::OBJECT_CENTER, "").c_str());
                        primitives.push_front(std::make_shared<Sphere>(ParserTags::OBJECT_SPHERE, radius, center));
                        // std::cout << "read " << ParserTags::OBJECT_SPHERE << " with radius " << radius << "and center (" << center << ")\n";
                    }
                }
                m_scene = std::make_shared<Scene>(bg, primitives);
            }

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

        inline void render() {
            auto w = m_camera->film.width;
            auto h = m_camera->film.height;
            // for ( int j = h-1 ; j >= 0 ; j-- ) {
            for (int j = 0; j < h; j++) {
                for (int i = 0; i < w; i++) {

                    // Ray ray = m_camera->generate_ray(i, j);

                    // std::cout << "Pixel: [" << i << ", " << j <<"] "
                    //         << "Ray [" << ray << "]" << std::endl;


                    // auto color = m_scene->background.sample(float(i) / float(w), float(j) / float(h)); // get background color.
                    // m_camera->film.add(Point2(i, j), color); // set image buffer at position (i,j), accordingly.

                    // ------------ prj03 ---------------------------------------------
                    Ray ray = m_camera->generate_ray(i, j);

                    auto color = m_scene->background.sample(float(i) / float(w), float(j) / float(h)); // get background color.
                    for (auto p : m_scene->objs) {
                        // Each time the ray hits something, max_t parameter of the ray must be updated.
                        if (p->intersect_p(ray)) // Does the ray hit any sphere in the scene?
                            color = rgb(255, 0, 0);  // Just paint it red.
                    }

                    // sample background
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