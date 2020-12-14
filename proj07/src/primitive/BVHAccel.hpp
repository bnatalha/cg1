#ifndef BVH_ACCEL_HPP
#define BVH_ACCEL_HPP

#include "aggregate_primitive.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>


namespace rt3 {

    class BVHAccel : public AggregatePrimitive {
    public:

        BVHAccel(const std::vector<std::shared_ptr<Primitive>>& list)
            : BVHAccel(list, 0, list.size())
        {}

        BVHAccel(
            const std::vector<std::shared_ptr<Primitive>>& src_objects,
            size_t start, size_t end);

        virtual ~BVHAccel() = default;

    public:
        std::vector<std::shared_ptr<Primitive>> primitives;
        std::shared_ptr<Primitive> left;
        std::shared_ptr<Primitive> right;
        aabb box;

        // bool hit(const Ray& r, float t_min, float t_max, Surfel* rec) const;

        Point3 world_bounds() const;
        bool bounding_box(float t0, float t1, aabb& output_box) const;
        bool intersect(const Ray& ray, float& t_min, float& t_max, Surfel* sf) const;
        bool intersect_p(const Ray& ray, float& hit1, float& hit2) const;
    };

    bool box_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b, int axis);

    bool box_x_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b);

    bool box_y_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b);

    bool box_z_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b);
}

#endif