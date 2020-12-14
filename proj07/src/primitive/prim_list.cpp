#include "prim_list.hpp"

namespace rt3 {

    Point3 PrimList::world_bounds() const {
        std::cerr << "not implemented\n";
        throw std::logic_error("not implemented");
    }

    bool PrimList::bounding_box(float t0, float t1, aabb& box) const {
        std::cerr << "not implemented\n";
        throw std::logic_error("not implemented");
    }

    bool PrimList::intersect(const Ray& ray, float& t_min, float& t_max, Surfel* sf) const {

        bool result = false;

        for (auto prim : primitives) {
            if (prim->intersect(ray, t_min, t_max, sf)) {
                result = true;
            }
        }
        return result;

    }

    bool PrimList::intersect_p(const Ray& ray, float& hit1, float& hit2) const {
        for (auto p : primitives) {
            if (p->intersect_p(ray, hit1, hit2)) {
                return true;
            }
        }
        return false;
    }
}