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

        virtual Point3 world_bounds() const =0;
        // const Ray& ray (in), float *t_hit (out), Surfel* sf (out)
        virtual bool intersect(const Ray& ray, float *t_hit, Surfel* sf) const =0;
        virtual bool intersect_p(const Ray& ray) const=0;

        virtual void print() =0;
    };


}

#include "primitive/sphere.hpp"
#include "primitive/triangle.hpp"

#endif