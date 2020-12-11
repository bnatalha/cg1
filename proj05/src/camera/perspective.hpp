#ifndef CAMERA_PERSPECTIVE_HPP
#define CAMERA_PERSPECTIVE_HPP

#include "core/camera.hpp"

namespace rt3 {

    class PerspectiveCamera : public Camera {

    public:
        int fovy;

        PerspectiveCamera() {};
        PerspectiveCamera(std::string t, float fovy) : Camera(t), fovy(fovy) {}
        virtual ~PerspectiveCamera() = default;

        void set_lrbt();

        void print();

        Ray generate_ray(float x, float y);
        Ray generate_ray(int x, int y);
    };

}

#endif
