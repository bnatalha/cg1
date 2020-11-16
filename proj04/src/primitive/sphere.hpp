#ifndef PRIMITIVE_SPHERE_HPP
#define PRIMITIVE_SPHERE_HPP

#include "core/primitive.hpp"

namespace rt3 {
    // class Primitive;
    class Sphere : public Primitive {
    public:
        float r;
        Point3 c;

        Sphere(string type, float r, Point3 c) : Primitive(type), r(r), c(c) {}
        virtual ~Sphere() = default;

        bool intersect(const Ray& ray, Surfel* sf) const;
        bool intersect_p(const Ray& ray) const;

        void print();
    };


}


#endif