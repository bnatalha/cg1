#ifndef PRIM_LIST_HPP
#define PRIM_LIST_HPP

#include "aggregate_primitive.hpp"
#include <vector>
#include <iostream>

namespace rt3 {
    class PrimList : public AggregatePrimitive {
    public:
        std::vector<std::shared_ptr<Primitive>> primitives;

        PrimList(std::vector<std::shared_ptr<Primitive>> prim) : primitives(prim) {}
        virtual ~PrimList() = default;

        Point3 world_bounds() const;
        bool bounding_box(float t0, float t1, aabb& box) const;
        bool intersect(const Ray& ray, float& t_min, float& t_max, Surfel* sf) const;
        bool intersect_p(const Ray& ray, float& hit1, float& hit2) const;
    };
}

#endif