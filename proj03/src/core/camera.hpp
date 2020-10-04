#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>

#include "header.hpp"
#include "film.hpp"
#include "ray.hpp"
#include "paramset.hpp"
#include "tinyxml2.hpp"
#include <cmath>

using namespace tinyxml2;

namespace rt3 {

    using std::string;
    using std::unique_ptr;
    using std::unordered_map;
    using std::vector;

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
        Camera(string type) : type(type) { }
        virtual ~Camera() {};

        void set_lrbt(float ml, float mr, float mb, float mt) {
            if (!has_screen_window) {
                l = ml;
                r = mr;
                b = mb;
                t = mt;
                has_screen_window = true;
            }
        }

        virtual void set_lrbt() = 0;

        virtual void print() {
            std::cout << "--------------- Camera -----------------\n";
            std::cout << "type: " << type << "\n";
            std::cout << "lrbt: ["
                << l << " "
                << r << " "
                << b << " "
                << t << "]\n";
        }

        // camera orthogonal basis u,v and w
        Vector3 gaze;   // look_at - look_from
        Vector3 _w;
        Vector3 _u;
        Vector3 _v;
        Point3 e;
        float fd = 1;  // focal distance

        // pixel (i,j) -> point (u,v)
        // TODO(bnatalha): verify if using int/float will make a difference
        Point2 to_screen_space(Point2 pixel) {
            float u = l + (r - l) * (pixel.first + 0.5) / film.width;
            float v = b + (t - b) * (pixel.second + 0.5) / film.height;
            return Point2(u, v);
        }

        virtual Ray generate_ray(int x, int y) = 0;
        virtual Ray generate_ray(float x, float y) = 0;

    };

    class OrtographicCamera : public Camera {

    public:
        OrtographicCamera() {}
        OrtographicCamera(string type) : Camera(type) {}
        // OrtographicCamera(string type, float l, float r, float b, float t) : Camera(type, l, r, b, t) {}
        virtual ~OrtographicCamera() = default;

        inline void set_lrbt() {
            if (!has_screen_window) {
                // TODO(bnatalha): check if this screen_window calculation is okay
                // if no screen_window is provided, do this;
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

        inline void print() {
            Camera::print();
            film.print();
        }

        inline Ray generate_ray(float x, float y) {
            Point2 p = to_screen_space(Point2(x, y));
            float u = p.first, v = p.second;
            Vector3 d = _w;
            Point3 o = e + (u * _u) + (v * _v);
            return Ray(o, d);
        }
        inline Ray generate_ray(int x, int y) {
            Point2 p = to_screen_space(Point2(x, y));
            float u = p.first, v = p.second;
            Vector3 d = _w;
            Point3 o = e + (u * _u) + (v * _v);
            return Ray(o, d);
        }
    };

    class PerspectiveCamera : public Camera {

    public:
        int fovy;

        PerspectiveCamera() {};
        PerspectiveCamera(string t, int fovy) : Camera(t), fovy(fovy) {}
        virtual ~PerspectiveCamera() = default;

        inline void set_lrbt() {
            if (!has_screen_window) {
                float H = film.height / 2;
                // TODO(bnatalha): use tangent calculation
                // float tg = float (tan(fovy / 2.0))s;
                // float tg = float (2.0);
                float tg = H / fd;
                float a = film.aspect_ratio();
                l = -a * tg;
                r = a * tg;
                b = -(1 / film.aspect_ratio());
                t = 1 / film.aspect_ratio();
            }
        }

        inline void print() {
            Camera::print();
            std::cout << "fovy " << fovy << "\n";
            film.print();
        }

        inline Ray generate_ray(float x, float y) {
            Point2 p = to_screen_space(Point2(x, y));
            float u = p.first, v = p.second;
            Vector3 d = (fd * _w) + (u * _u) + (v * _v);
            Point3 o = e;
            return Ray(o, d);
        }
        inline Ray generate_ray(int x, int y) {
            Point2 p = to_screen_space(Point2(x, y));
            float u = p.first, v = p.second;
            Vector3 d = (fd * _w) + (u * _u) + (v * _v);
            Point3 o = e;
            return Ray(o, d);
        }
    };


}  // namespace rt3

#endif