#ifndef FILM_HPP
#define FILM_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
// #include "external/tinyxml2.hpp"
#include "external/lodepng.hpp"
#include "vector3.hpp"

namespace rt3 {

    /**
     * Handles pixels values as an image color buffer. This allows the ray tracer to save the color buffer to an image file in PPM or PNG format.
     * */
    class Film
    {
    public:
        std::string type;
        int height;
        int width;
        std::string filename;
        std::string img_type;

        std::vector<rgb> buffer;

        Film() {}
        Film(std::string t, int y, int x, std::string fn, std::string imgt);
        ~Film() {}

        float aspect_ratio();
        int index_of(Point2& p);
        void add(Point2 p, rgb color);

        void write_image();
        void print();
    };

}

#endif