#ifndef FILM_HPP
#define FILM_HPP

#include "header.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "tinyxml2.h"
#include "lodepng.h"

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

    // std::shared_ptr<std::vector<int>> buffer;
    std::vector<rgb> buffer;

    Film() {}
    Film(std::string t, int y, int x, std::string fn, std::string imgt) : type(t), height(y), width(x), filename(fn), img_type(imgt)
    {
        // buffer.reserve(width * height);
        buffer = std::vector<Pixel>(width * height, rgb(0, 0, 0));
    }
    ~Film() {}

    // checar ordem de crescimento
    int index_of(Point2 &p)
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

        if (img_type.compare("PPM") == 0)
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
            std::vector<unsigned char> image(width * height, 0);
            for (int i = 0; i < width * height; i++)
            {
                int n;
                unsigned char uc;
                for (int idx = 0; idx < 3; idx++)
                {
                    n = (int)buffer[i][idx];
                    uc = (unsigned char) n;
                    image.push_back(uc);
                }
                uc = 255;
                image.push_back(uc);

            }

            unsigned error = lodepng::encode(filename, image, width, height);

            //if there's an error, display it
            if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
        }
    }

    // void init(){
    // buffer = std::make_shared<std::vector<int>>();
    // buffer->reserve(y_res * x_res);
    // }

    inline void print()
    {
        std::cout
            << type << " "
            << width << " "
            << height << " "
            << filename << " "
            << img_type << "\n";
    }

    // inline int parse(XMLNode *pRoot)
    // {
    //     const char* str = "default";
    //     int val;
    //     XMLElement *pElement;

    //     pElement = pRoot->FirstChildElement("film");
    //     pElement->QueryStringAttribute("type", &str);
    //     type = str;
    //     pElement->QueryIntAttribute("x_res", &val);
    //     x_res = val;
    //     pElement->QueryIntAttribute("y_res", &val);
    //     y_res = val;
    //     pElement->QueryStringAttribute("filename", &str);
    //     filename = str;
    //     pElement->QueryStringAttribute("img_type", &str);
    //     img_type = str;

    //     return XML_SUCCESS;
    // }
};

#endif