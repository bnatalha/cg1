#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>

#include "film.hpp"
#include "paramset.hpp"
#include "tinyxml2.hpp"

using namespace tinyxml2;

namespace rt3 {

    using std::string;
    using std::unique_ptr;
    using std::unordered_map;
    using std::vector;

    class Camera {
    public:
        std::string type;
        Film film;

        Camera() {}
        Camera(string t) : type(t) {}
        ~Camera() {}

        inline void print() {
            std::cout << "Camera type: " << type << "\n";
            film.print();
        }
    };

}  // namespace rt3

#endif