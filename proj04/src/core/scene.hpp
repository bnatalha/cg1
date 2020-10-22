#ifndef SCENE_HPP
#define SCENE_HPP

#include <forward_list>

#include "tinyxml2.hpp"
#include "background.hpp"
#include "primitive.hpp"

namespace rt3 {
    using namespace tinyxml2;

    class Scene
    {
    public:
        Background background;
        ObjectList objs;

        Scene() {}
        Scene(Background& bg) : background(bg) {}
        Scene(Background& bg, ObjectList& objs) : background(bg), objs(objs) {}
        ~Scene() {}

        inline void print() {
            std::cout << "--------------------- SCENE ---------------------\n";
            background.print();
            if (!objs.empty()) {
                std::cout << "{PRIMITIVES:}\n";
                for (auto p : objs) {
                    std::cout << "-------------------------\n";
                    p->print();
                    std::cout << "-------------------------\n";
                }
            }
        }
    };

}

#endif