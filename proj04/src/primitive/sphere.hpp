#ifndef PRIMITIVE_SPHERE_HPP
#define PRIMITIVE_SPHERE_HPP

#include "shape.hpp"
// #include "core/surfel.hpp"
// #include "core/ray.hpp"

namespace rt3 {
    // class Primitive;
    class Sphere : public Shape {
    public:
        float r; //!< radius
        Point3 c; //!< center

        // Sphere(string type, float r, Point3 c) : Shape(type), r(r), c(c) {}
        Sphere(float r, Point3 c, bool flip_n) : Shape(flip_n), r(r), c(c) {}
        virtual ~Sphere() = default;

        Point3 world_bounds() const;

        bool intersect(const Ray& ray, float* t_hit, Surfel* sf) const;
        bool intersect_p(const Ray& ray) const;

        void print();
    };


}


#endif