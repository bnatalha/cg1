#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>

#include <cmath>
#include "core/film.hpp"
#include "core/ray.hpp"
// #include "core/paramset.hpp"
#include "header.hpp"

namespace rt3 {
    class Camera {
    public:
        std::string type;
        bool has_screen_window = false;
        Film film;

        // screen_window
        float l;
        float r;
        float b;
        float t;

        Camera() { }
        Camera(std::string type) : type(type) { }
        virtual ~Camera() {};

        void set_lrbt(float ml, float mr, float mb, float mt);

        virtual void set_lrbt() = 0;

        virtual void print();

        // camera orthogonal basis u,v and w
        Vector3 gaze;   // look_at - look_from
        Vector3 _w;
        Vector3 _u;
        Vector3 _v;
        Point3 e;
        float fd = 1;  // focal distance

        // pixel (i,j) -> point (u,v)
        // TODO(bnatalha): verify if using int/float will make a difference
        Point2f to_screen_space(Point2 pixel);

        virtual Ray generate_ray(int x, int y) = 0;
        virtual Ray generate_ray(float x, float y) = 0;
    };
}  // namespace rt3

#include "camera/ortographic.hpp"
#include "camera/perspective.hpp"

#endif
