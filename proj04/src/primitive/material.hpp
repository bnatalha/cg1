#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "core/surfel.hpp"
#include "core/ray.hpp"

namespace rt3 {
    class Surfel;

    class Material {
    public: 
        Material() {};
        virtual ~Material() {};

        // (Surfel *isec (out), Ray *r (out))
        virtual void scatter(Surfel* isec, Ray* r) = 0;
    };
}

#endif