#include "scene.hpp"

namespace rt3 {


    void Scene::print() {
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

}