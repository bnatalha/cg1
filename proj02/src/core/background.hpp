#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "header.hpp"
#include "vector3.hpp"
#include "tinyxml2.hpp"

using std::string;

namespace rt3 {

    /**
     * Is responsible for returning a color each time the primary ray misses any object in the scene (i.e. hits nothing).
     * */
    class Background
    {
    public:
        bool hasCornerColors;
        std::string type;
        std::string mapping;
        rgb color;
        rgb bl; // (0,0)
        rgb tl; // (0,1)
        rgb tr; // (1,1)
        rgb br; // (1,0)

        Background() {}
        Background(bool corner, string t, string mp, string c, string mBL, string mTL, string mTR, string mBR) : hasCornerColors(corner), type(t), mapping(mp), color(c.c_str())
        {
            bl = rgb(hasCornerColors ? mBL.c_str() : DEFAULT_COLOR);
            tl = rgb(hasCornerColors ? mTL.c_str() : DEFAULT_COLOR);
            tr = rgb(hasCornerColors ? mTR.c_str() : DEFAULT_COLOR);
            br = rgb(hasCornerColors ? mBR.c_str() : DEFAULT_COLOR);

        }
        ~Background() {}

        inline rgb sample(float x, float y)
        {
            if (!hasCornerColors)
            {
                return color;
            }

            // formula:
            // auto r = bl*(1-x)*(1-y)
            //     + br*x*(1-y)
            //     + tl*(1-x)*y
            //     + tr*x*y;

            // modified y axis formula:
            auto r = tl * (1 - x) * (1 - y)
                + tr * x * (1 - y)
                + bl * (1 - x) * y
                + br * x * y;

            return r;
        }

        inline void print()
        {
            std::cout << " {----- background -----}\n"
                << (hasCornerColors ? "" : "!") << "hasProvidedCorners" << " "
                << mapping << " "
                << type << " "
                << color;
            if (hasCornerColors) {
                std::cout << '\n'
                    << "bl: [" << bl << "]\n"
                    << "tl: [" << tl << "]\n"
                    << "tr: [" << tr << "]\n"
                    << "br: [" << br << "]";
            }
            std::cout << '\n';

        }
    };

}

#endif