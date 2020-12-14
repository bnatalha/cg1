#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "core/surfel.hpp"
#include "core/ray.hpp"

namespace rt3 {
    // class Primitive;
    class Shape {
    public:
        bool flip_normals = false;

        Shape(bool flip_n) : flip_normals(flip_n) {}
        virtual ~Shape() = default;

        virtual Point3 world_bounds() const = 0;
        // const Ray& ray (in), float *t_hit (out), Surfel* sf (out)
        virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;

        virtual bool intersect(const Ray& ray, float& t_min, float& t_max, Surfel* sf) const = 0;
        virtual bool intersect_p(const Ray& ray, float& hit1, float& hit2) const = 0;

        virtual void print() = 0;
    };


}

#include "primitive/sphere.hpp"
#include "primitive/triangle.hpp"

#endif