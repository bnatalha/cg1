#ifndef FILM_HPP
#define FILM_HPP

#include <iostream>

/**
 * Handles pixels values as an image color buffer. This allows the ray tracer to save the color buffer to an image file in PPM or PNG format.
 * */
class Film
{
public:
    std::string type;
    int y_res;
    int x_res;
    std::string filename;
    std::string img_type;

    Film() {}
    ~Film() {}

    inline void print()
    {
        std::cout
            << type << " "
            << x_res << " "
            << y_res << " "
            << filename << " "
            << img_type << "\n";
    }
};

#endif