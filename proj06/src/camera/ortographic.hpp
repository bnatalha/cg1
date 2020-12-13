#ifndef CAMERA_ORTOGRAPHIC_HPP
#define CAMERA_ORTOGRAPHIC_HPP

#include "core/camera.hpp"

namespace rt3 {


class OrtographicCamera : public Camera {

    public:
        OrtographicCamera() {}
        OrtographicCamera(std::string type) : Camera(type) {}
        // OrtographicCamera(string type, float l, float r, float b, float t) : Camera(type, l, r, b, t) {}
        virtual ~OrtographicCamera() = default;

        void set_lrbt();

        void print();

        Ray generate_ray(float x, float y);
        Ray generate_ray(int x, int y);
    };

}

#endif