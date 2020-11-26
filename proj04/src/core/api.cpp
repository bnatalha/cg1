#include "api.hpp"

namespace rt3 {

    using std::string;

    //  ============================= Camera ============================

    std::shared_ptr<Camera> API::camera(ParamSet_ptr& ps_camera, ParamSet_ptr& ps_film, ParamSet_ptr& ps_lookat) {
        std::stringstream sstr;

        string type = ps_camera->find_one<string>(ParserTags::CAMERA_TYPE, ParserTags::CAMERA_TYPE_ORTOGRAPHIC);
        std::shared_ptr<Camera> camera_ptr;

        // PERSPECTIVE
        if (type.compare(ParserTags::CAMERA_TYPE_PERSPECTIVE) == 0) {
            int fovy = ps_camera->find_one<int>(ParserTags::CAMERA_FOVY, 30);
            camera_ptr = std::make_shared<PerspectiveCamera>(type, fovy);
        }
        else {  // ORTAGRAPHIC
            camera_ptr = std::make_shared<OrtographicCamera>(type);
            string screen_window = ps_camera->find_one<string>(ParserTags::CAMERA_SCREEN_WINDOW, ParserTags::PARSER_DEFAULT_STR);
            if (screen_window.compare(ParserTags::PARSER_DEFAULT_STR) != 0) {
                float l, r, b, t;
                sstr << screen_window;
                sstr >> l >> r >> b >> t;
                camera_ptr->set_lrbt(l, r, b, t);
            }
        }

        // film
        type = ps_film->find_one<string>(ParserTags::FILM_TYPE, "default");
        string filename = ps_film->find_one<string>(ParserTags::FILM_FILENAME, "test_img.png");
        string img_type = ps_film->find_one<string>(ParserTags::FILM_IMG_TYPE, "PNG");
        int y_res = ps_film->find_one<int>(ParserTags::FILM_Y_RES, 100);
        int x_res = ps_film->find_one<int>(ParserTags::FILM_X_RES, 200);
        camera_ptr->film = Film(type, y_res, x_res, filename, img_type);
        camera_ptr->set_lrbt();

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

        camera_ptr->gaze = gaze;
        camera_ptr->_w = w;
        camera_ptr->_u = u;
        camera_ptr->_v = v;
        camera_ptr->e = look_from;

        return camera_ptr;
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

        // Background bg(providedCorners, t, mp, color, bl, tl, tr, br);
        std::shared_ptr<Background> bg = std::make_shared<Background>(providedCorners, t, mp, color, bl, tl, tr, br);

        // Objects
        if (primitives.empty()) {
            m_scene = std::make_shared<Scene>(std::move(bg));
        }
        else {
            std::vector<shared_ptr<Primitive>> prim_vec = std::vector<shared_ptr<Primitive>>();
            for (std::pair<ParamSet_ptr, ParamSet_ptr> ps_obj_pair : primitives) {
                if (ps_obj_pair.first->find_one<bool>(ParserTags::OBJECT_SPHERE, false)) {
                    float radius = ps_obj_pair.first->find_one<float>(ParserTags::OBJECT_RADIUS, -23423.f);
                    Point3 center = Point3(ps_obj_pair.first->find_one<string>(ParserTags::OBJECT_CENTER, "").c_str());

                    string material_type = ps_obj_pair.second->find_one<string>(ParserTags::MATERIAL_TYPE, ParserTags::MATERIAL_TYPE_FLAT).c_str();
                    // if FlatMaterial
                    Point3 material_color = Point3(ps_obj_pair.second->find_one<string>(ParserTags::MATERIAL_COLOR, "200 100 200").c_str());
                    std::shared_ptr<Material> material = std::make_shared<FlatMaterial>(material_color);
                    std::shared_ptr<Shape> shape = std::make_shared<Sphere>(radius, center, false);

                    std::shared_ptr<Primitive> geo_prim = std::make_shared<GeometricPrimitive>(std::move(material), std::move(shape));

                    prim_vec.push_back(std::move(geo_prim));
                }
            }
            std::shared_ptr<Primitive> primitive = std::make_shared<PrimList>(prim_vec);
            m_scene = std::make_shared<Scene>(std::move(bg), std::move(primitive));
        }

    }

    void API::integrator(ParamSet_ptr& ps_it, std::shared_ptr<Camera> camera) {
        string type = ps_it->find_one<string>(ParserTags::INTEGRATOR_TYPE, ParserTags::INTEGRATOR_TYPE_FLAT);
        if (type.compare(ParserTags::INTEGRATOR_TYPE_FLAT) == 0) {
            m_integrator = std::make_shared<FlatIntegrator>(std::move(camera));
        }
    }

    // ================================== Aux ==================================
    void API::print() {
        if (m_verbose) {
            // m_camera->print();
            m_scene->print();
        }
    }

    // ============================ Main functions ================================

    void API::render() {
        m_integrator->render(*(m_scene.get()));
    }

    void API::save() {
        m_integrator->camera->film.write_image();
    }

    void API::run(std::unordered_map<const char*, ParamSet_ptr>& paramsets,
        std::forward_list<std::pair<ParamSet_ptr, ParamSet_ptr>>& primitives) {

        // instantiate
        std::shared_ptr<Camera> camera_ptr = camera(paramsets[ParserTags::CAMERA], paramsets[ParserTags::FILM], paramsets[ParserTags::LOOKAT]);
        scene(paramsets[ParserTags::BACKGROUND], primitives);
        integrator(paramsets[ParserTags::INTEGRATOR], std::move(camera_ptr));

        print();
        render();
        save();
    }
}