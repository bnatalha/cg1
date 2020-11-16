#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <forward_list>
#include <memory>

#include "surfel.hpp"
#include "ray.hpp"
#include "vector3.hpp"


namespace rt3 {

    class Primitive {
    public:
        std::string type;

        Primitive(string type) : type(type) {}
        virtual ~Primitive() {};

        virtual bool intersect(const Ray& ray, Surfel* sf) const = 0;
        // Simpler & faster version of intersection that only return true/false.
        // It does not compute the hit point information.
        virtual bool intersect_p(const Ray& ray) const = 0;
        virtual void print();
        //     virtual const Material* get_material(void) const = { return material; }
        // private:
        //     std::shared_ptr<Material> material;
    };

    typedef std::forward_list<std::shared_ptr<Primitive>> ObjectList;

}


#endif