#include "scene.hpp"

namespace rt3 {

    bool Scene::intersect(const Ray& r, Surfel* isect) const{
        return primitive->intersect(r, isect);
    }

    bool Scene::intersect_p(const Ray& r) const {
        return primitive->intersect_p(r);
    }


    void Scene::print() {
        std::cout << "--------------------- SCENE ---------------------\n";
        background->print();
        // if (!objs.empty()) {
        //     std::cout << "{PRIMITIVES:}\n";
        //     for (auto p : objs) {
        //         std::cout << "-------------------------\n";
        //         p->print();
        //         std::cout << "-------------------------\n";
        //     }
        // }
    }

}