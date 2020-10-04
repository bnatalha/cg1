#ifndef FILM_HPP
#define FILM_HPP

#include "header.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "tinyxml2.hpp"
#include "lodepng.hpp"

namespace rt3 {

    using namespace tinyxml2;

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
        Film(std::string t, int y, int x, std::string fn, std::string imgt) : type(t), height(y), width(x), filename(fn), img_type(imgt)
        {
            // buffer.reserve(width * height);
            buffer = std::vector<Pixel>(width * height, rgb(0, 0, 0));

            // aspectration
        }
        ~Film() {}

        float aspect_ratio() { return float(width) / float(height); }

        // checar ordem de crescimento
        int index_of(Point2& p)
        {
            return p.first + (width * p.second);
        }

        inline void add(Point2 p, rgb color)
        {
            buffer[index_of(p)] = color;
        }

        inline void write_image()
        {
            std::ofstream ofs(filename, std::ios::binary);

            if (img_type.compare("PPM") == 0 || img_type.compare("ppm") == 0)   // PPM
            {
                ofs << "P3\n"
                    << width << " " << height << "\n"
                    << "255\n";
                for (auto c : buffer)
                {
                    ofs << int(c.r()) << " "
                        << int(c.g()) << " "
                        << int(c.b()) << "\n";
                }
            }
            else // PNG
            {
                std::vector<unsigned char> image;
                for (long unsigned i = 0; i < buffer.size(); i++)
                {
                    int n;
                    unsigned char uc;
                    for (int idx = 0; idx < 3; idx++)   // R, G & B pixel value
                    {
                        n = (int)buffer[i][idx];
                        uc = (unsigned char)n;
                        image.push_back(uc);
                    }
                    uc = 255;   // alpha
                    image.push_back(uc);

                }

                unsigned error = lodepng::encode(filename, image, width, height);

                // if there's an error, display it
                if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
            }
        }

        inline void print()
        {
            std::cout
                << type << " "
                << width << " "
                << height << " "
                << filename << " "
                << img_type << "\n";
        }
    };

}

#endif