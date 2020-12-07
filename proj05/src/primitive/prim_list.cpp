#include "prim_list.hpp"

namespace rt3 {

    Point3 PrimList::world_bounds() const {
        std::cerr << "not implemented\n";
        throw std::logic_error("not implemented");
    }
    bool PrimList::intersect(const Ray& ray, Surfel* sf) const {

        bool result = false;
        // Surfel* aux_sf = new Surfel();
        // ray.t_max = 0.f;
        // ray.t_min = 0.f;

        for (auto prim : primitives) {
            // if (prim->intersect(ray, aux_sf)) {
            if (prim->intersect(ray, sf)) {
                // if (aux_sf->primitive == nullptr) {
                    result = true;
                //     aux_sf->primitive = prim.get();
                //     *sf = *aux_sf;
                //     continue;
                // }

                // if (aux_sf->t_hit < sf->t_hit) {
                //     aux_sf->primitive = prim.get();
                    // *sf = *aux_sf;
                // }

                

            }
        }

        // delete aux_sf;

        return result;

    }

    bool PrimList::intersect_p(const Ray& ray) const {
        for (auto p : primitives) {
            if (p->intersect_p(ray)) {
                return true;
            }
        }
        return false;
    }
}