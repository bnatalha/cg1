#ifndef CAMERA_PERSPECTIVE_HPP
#define CAMERA_PERSPECTIVE_HPP

#include "core/camera.hpp"

namespace rt3 {

    class PerspectiveCamera : public Camera {

    public:
        int fovy;

        PerspectiveCamera() {};
        PerspectiveCamera(std::string t, int fovy) : Camera(t), fovy(fovy) {}
        virtual ~PerspectiveCamera() = default;

        void set_lrbt();

        inline void print();

        inline Ray generate_ray(float x, float y);
        inline Ray generate_ray(int x, int y);
    };

}

#endif
