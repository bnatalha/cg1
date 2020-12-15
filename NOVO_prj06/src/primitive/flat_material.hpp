#ifndef FLAT_MATERIAL_HPP
#define FLAT_MATERIAL_HPP

#include "material.hpp"
// #include "core/surfel.hpp"
// #include "core/ray.hpp"

namespace rt3 {
    class Surfel;

    class FlatMaterial : public Material {
    public:
        rgb kd; //!< color

        FlatMaterial(rgb color) : kd(color) {};
        virtual ~FlatMaterial() = default;

        void scatter(Surfel *isec, Ray *r);
    };

}

#endif