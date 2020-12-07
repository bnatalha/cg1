#ifndef BLINN_PHONG_MATERIAL_HPP
#define BLINN_PHONG_MATERIAL_HPP

#include "material.hpp"

namespace rt3 {

    class BlinnPhongMaterial
    {
    public:
        string name;
        Vector3 ka; // ambient [0, 1]
        Vector3 kd; // difuse
        Vector3 ks; // specular
        float g; // glossiness (phong)

        BlinnPhongMaterial(/* args */);
        ~BlinnPhongMaterial();

    };
}

#endif