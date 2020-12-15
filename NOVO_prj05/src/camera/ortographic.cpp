#include "ortographic.hpp"

namespace rt3 {

    void OrtographicCamera::set_lrbt() {
        if (!has_screen_window) {
            if (film.aspect_ratio() > 1.0) {
                b = -1;
                t = 1;
                l = -film.aspect_ratio();
                r = film.aspect_ratio();
            }
            else {
                l = -1;
                r = 1;
                b = -(1 / film.aspect_ratio());
                t = 1 / film.aspect_ratio();
            }
        }
    }

    void OrtographicCamera::print() {
        Camera::print();
        film.print();
    }

    Ray OrtographicCamera::generate_ray(float x, float y) {
        return generate_ray(int(floor(x)), int(floor(y)));
    }
    Ray OrtographicCamera::generate_ray(int x, int y) {
        Point2f p = to_screen_space(Point2(x, y));
        float u = p.first, v = p.second;
        Vector3 d = _w;
        Point3 o = e + (u * _u) + (v * _v);
        return Ray(o, d);
    }
}