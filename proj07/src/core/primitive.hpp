#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <forward_list>
#include <memory>

#include "surfel.hpp"
#include "ray.hpp"
#include "vector3.hpp"
#include "aabb.hpp"
#include "primitive/material.hpp"

namespace rt3 {

    class Surfel;
    class Material;

    class Primitive {
    public:
        std::string type;

        Primitive(string type) : type(type) {}
        Primitive() : type("not provided") {}
        virtual ~Primitive() {};

        // TODO: what is Bouds3f ?
        virtual Point3 world_bounds() const = 0;
        virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;
        virtual bool intersect(const Ray& ray, float& t_min, float& t_max, Surfel* sf) const = 0;
        // virtual bool intersect_p(const Ray& ray) const = 0;
        virtual bool intersect_p(const Ray& ray, float& hit1, float& hit2) const = 0;
        virtual void print();
        virtual const Material* get_material(void) const = 0;
    };

    // typedef std::forward_list<std::shared_ptr<Primitive>> ObjectList;

}

// #include "primitive/sphere.hpp"

#endif