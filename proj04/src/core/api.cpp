#include "api.hpp"

namespace rt3 {

    using std::string;

    //  ============================= Camera ============================

    void API::camera(ParamSet_ptr& ps_camera, ParamSet_ptr& ps_film, ParamSet_ptr& ps_lookat) {
        std::stringstream sstr;

        string type = ps_camera->find_one<string>(ParserTags::CAMERA_TYPE, ParserTags::CAMERA_TYPE_ORTOGRAPHIC);

        // PERSPECTIVE
        if (type.compare(ParserTags::CAMERA_TYPE_PERSPECTIVE) == 0) {
            int fovy = ps_camera->find_one<int>(ParserTags::CAMERA_FOVY, 30);
            m_camera = std::make_shared<PerspectiveCamera>(type, fovy);
        }
        else {  // ORTAGRAPHIC
            m_camera = std::make_shared<OrtographicCamera>(type);
            string screen_window = ps_camera->find_one<string>(ParserTags::CAMERA_SCREEN_WINDOW, ParserTags::PARSER_DEFAULT_STR);
            if (screen_window.compare(ParserTags::PARSER_DEFAULT_STR) != 0) {
                float l, r, b, t;
                sstr << screen_window;
                sstr >> l >> r >> b >> t;
                m_camera->set_lrbt(l, r, b, t);
            }
        }

        // film
        type = ps_film->find_one<string>(ParserTags::FILM_TYPE, "default");
        string filename = ps_film->find_one<string>(ParserTags::FILM_FILENAME, "test_img.png");
        string img_type = ps_film->find_one<string>(ParserTags::FILM_IMG_TYPE, "PNG");
        int y_res = ps_film->find_one<int>(ParserTags::FILM_Y_RES, 100);
        int x_res = ps_film->find_one<int>(ParserTags::FILM_X_RES, 200);
        m_camera->film = Film(type, y_res, x_res, filename, img_type);
        m_camera->set_lrbt();

        // lookat
        // string look_at;
        // string look_from;
        // string up;
        // bool hasLookat = ps_camera->find_one<bool>(ParserTags::LOOKAT, false);
        // if (hasLookat) {
        // }
        Vector3 look_at = Vector3(ps_lookat->find_one<string>(ParserTags::LOOKAT_LOOK_AT, "0 0 0").c_str());
        Vector3 look_from = Vector3(ps_lookat->find_one<string>(ParserTags::LOOKAT_LOOK_FROM, "0 0 0").c_str());
        Vector3 vup = Vector3(ps_lookat->find_one<string>(ParserTags::LOOKAT_UP, "0 0 0").c_str());

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

    // ========================== Scene =================================

    string API::sample_corner_color(const char* corner_name, bool& flag, ParamSet_ptr& ps) {
        string foundCorner = ps->find_one<string>(corner_name, "not_provided");
        string corner = DEFAULT_COLOR;
        if (foundCorner.compare("not_provided") != 0) {
            corner = foundCorner;
            flag = true;
        }
        return corner;
    }

    // TODO(bnatalha): function for background parsing only
    void API::scene(ParamSet_ptr& ps_bg, std::forward_list<std::pair<ParamSet_ptr, ParamSet_ptr>>& primitives) {

        // BACKGROUND
        string t = ps_bg->find_one<string>(ParserTags::BACKGROUND_TYPE, "default");
        string mp = ps_bg->find_one<string>(ParserTags::BACKGROUND_MAPPING, DEFAULT_MAPPING);
        string color = ps_bg->find_one<string>(ParserTags::BACKGROUND_COLOR, DEFAULT_COLOR);

        bool providedCorners = false;

        string tl = sample_corner_color(ParserTags::BACKGROUND_TL, providedCorners, ps_bg);
        string bl = sample_corner_color(ParserTags::BACKGROUND_BL, providedCorners, ps_bg);
        string tr = sample_corner_color(ParserTags::BACKGROUND_TR, providedCorners, ps_bg);
        string br = sample_corner_color(ParserTags::BACKGROUND_BR, providedCorners, ps_bg);

        Background bg(providedCorners, t, mp, color, bl, tl, tr, br);

        // Objects
        if (primitives.empty()) {
            m_scene = std::make_shared<Scene>(bg);
        }
        else {
            ObjectList objects = ObjectList();
            for (std::pair<ParamSet_ptr, ParamSet_ptr> ps_obj_pair : primitives) {
                if (ps_obj_pair.first->find_one<bool>(ParserTags::OBJECT_SPHERE, false)) {
                    float radius = ps_obj_pair.first->find_one<float>(ParserTags::OBJECT_RADIUS, -23423.f);
                    Point3 center = Point3(ps_obj_pair.first->find_one<string>(ParserTags::OBJECT_CENTER, "").c_str());
                    // treat material

                    objects.push_front(std::make_shared<Sphere>(ParserTags::OBJECT_SPHERE, radius, center));
                    // std::cout << "read " << ParserTags::OBJECT_SPHERE << " with radius " << radius << "and center (" << center << ")\n";
                }
            }
            m_scene = std::make_shared<Scene>(bg, objects);
        }

    }

    // ================================== Aux ==================================
    void API::print() {
        if (m_verbose) {
            m_camera->print();
            m_scene->print();
        }
    }

    // ============================ Main functions ================================

    void API::render() {
        auto w = m_camera->film.width;
        auto h = m_camera->film.height;
        // for ( int j = h-1 ; j >= 0 ; j-- ) {
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {

                // ------------ prj02 ---------------------------------------------
                // Ray ray = m_camera->generate_ray(i, j);

                // std::cout << "Pixel: [" << i << ", " << j <<"] "
                //         << "Ray [" << ray << "]" << std::endl;


                // auto color = m_scene->background.sample(float(i) / float(w), float(j) / float(h)); // get background color.
                // m_camera->film.add(Point2(i, j), color); // set image buffer at position (i,j), accordingly.

                // ------------ prj03 ---------------------------------------------
                Ray ray = m_camera->generate_ray(i, j);

                auto color = m_scene->background.sample(float(i) / float(w), float(j) / float(h)); // get background color.
                for (auto p : m_scene->objs) {
                    if (p->intersect_p(ray)) {
                        color = rgb(255, 0, 0); // hit objects with red
                    }
                }

                m_camera->film.add(Point2(i, j), color); // set image buffer at position (i,j).
            }
        }
    }

    void API::save() {
        m_camera->film.write_image();
    }

    void API::run(std::unordered_map<const char*, ParamSet_ptr>& paramsets,
     std::forward_list<std::pair<ParamSet_ptr, ParamSet_ptr>>& primitives) {
         
        // instatiate
        camera(paramsets[ParserTags::CAMERA], paramsets[ParserTags::FILM], paramsets[ParserTags::LOOKAT]);
        scene(paramsets[ParserTags::BACKGROUND], primitives);

        print();
        render();
        save();
    }
}