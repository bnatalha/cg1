#ifndef PRIM_LIST_HPP
#define PRIM_LIST_HPP

#include "aggregate_primitive.hpp"
#include <vector>

namespace rt3 {
    class PrimList : public AggregatePrimitive {
    public:
        std::vector<std::shared_ptr<Primitive>> primitives;

        PrimList(std::vector<std::shared_ptr<Primitive>> prim) : primitives(prim) {}
        virtual ~PrimList() = default;

        Point3 world_bounds() const;
        bool intersect(const Ray& ray, Surfel* sf) const;
        bool intersect_p(const Ray& ray) const;
    };
}

#endif