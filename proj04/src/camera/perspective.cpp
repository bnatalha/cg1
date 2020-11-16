#include "perspective.hpp"

namespace rt3 {

    void PerspectiveCamera::set_lrbt() {
        if (!has_screen_window) {
            // float hh = film.height / 2.f;
            float r_angle = TO_RADIANS(float(fovy) / 2.f);
            float tg = tan(r_angle);
            // float tg = float (2.0);
            // float tg = hh / fd;
            // float tg = hh;
            float a = film.aspect_ratio();
            l = -a * tg;
            r = a * tg;
            b = -tg;
            t = tg;
        }
    }

    void PerspectiveCamera::print() {
        Camera::print();
        std::cout << "fovy " << fovy << "\n";
        film.print();
    }

    Ray PerspectiveCamera::generate_ray(float x, float y) {
        return generate_ray(int(floor(x)), int(floor(y)));
    }
    Ray PerspectiveCamera::generate_ray(int x, int y) {
        Point2f p = to_screen_space(Point2(x, y));
        float u = p.first, v = p.second;
        Vector3 d = (fd * _w) + (u * _u) + (v * _v);
        Point3 o = e;
        return Ray(o, d);
    }
}  // namespace rt3
