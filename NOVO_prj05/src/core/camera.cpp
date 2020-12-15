#include "camera.hpp"

namespace rt3 {

    void Camera::set_lrbt(float ml, float mr, float mb, float mt) {
        if (!has_screen_window) {
            l = ml;
            r = mr;
            b = mb;
            t = mt;
            has_screen_window = true;
        }
    }

    void Camera::print() {
        std::cout << "--------------- Camera -----------------\n";
        std::cout << "type: " << type << "\n";
        std::cout << "lrbt: ["
            << l << " "
            << r << " "
            << b << " "
            << t << "]\n";
    }

    Point2f Camera::to_screen_space(Point2 pixel) {
        float u = l + ((r - l) * (pixel.first + 0.5)) / film.width;
        float v = b + ((t - b) * (pixel.second + 0.5)) / film.height;
        return Point2f(u, v);
    }

}