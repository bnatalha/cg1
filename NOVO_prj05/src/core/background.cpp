#include "background.hpp"

namespace rt3 {

    Background::Background(bool corner, string t, string mp, string c, string mBL, string mTL, string mTR, string mBR) : hasCornerColors(corner), type(t), mapping(mp), color(c.c_str())
    {
        bl = rgb(hasCornerColors ? mBL.c_str() : DEFAULT_COLOR);
        tl = rgb(hasCornerColors ? mTL.c_str() : DEFAULT_COLOR);
        tr = rgb(hasCornerColors ? mTR.c_str() : DEFAULT_COLOR);
        br = rgb(hasCornerColors ? mBR.c_str() : DEFAULT_COLOR);

    }

    rgb Background::sample(float x, float y)
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

    void Background::print()
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

}