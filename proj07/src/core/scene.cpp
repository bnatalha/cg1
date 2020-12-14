#include "scene.hpp"

namespace rt3 {

    bool Scene::intersect(const Ray& ray, float& t_min, float& t_max, Surfel* isect) const {
        return primitive->intersect(ray, t_min, t_max, isect);
    }

    bool Scene::intersect_p(const Ray& ray, float& t_min, float& t_max) const {
        return primitive->intersect_p(ray, t_min, t_max);
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