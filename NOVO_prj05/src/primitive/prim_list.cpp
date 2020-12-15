#include "prim_list.hpp"

namespace rt3 {

    Point3 PrimList::world_bounds() const {
        std::cerr << "not implemented\n";
        throw std::logic_error("not implemented");
    }
    bool PrimList::intersect(const Ray& ray, Surfel* sf) const {

        bool result = false;

        for (auto prim : primitives) {
            if (prim->intersect(ray, sf)) {
                result = true;
            }
        }
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