#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "header.hpp"
#include "vector3.hpp"
#include "external/tinyxml2.hpp"

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
        Background(bool corner, std::string t, std::string mp, std::string c, std::string mBL, std::string mTL, std::string mTR, std::string mBR);
        ~Background() {}

        rgb sample(float x, float y);


        void print();
    };

}

#endif