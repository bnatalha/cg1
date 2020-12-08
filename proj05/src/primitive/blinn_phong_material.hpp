#ifndef BLINN_PHONG_MATERIAL_HPP
#define BLINN_PHONG_MATERIAL_HPP

#include "material.hpp"

namespace rt3 {
    class BlinnPhongMaterial : public Material
    {
    public:
        // string name;
        Vector3 ka; // ambient [0, 1]
        Vector3 kd; // difuse
        Vector3 ks; // specular
        Vector3 mirror; // specular
        float g; // glossiness (phong)

        // BlinnPhongMaterial(Vector3& mka, Vector3& mkd, Vector3& mks, Vector3& mmirror, float& mg);
        BlinnPhongMaterial(Vector3& mka, Vector3& mkd, Vector3& mks, Vector3& mmirror, float& mg) : ka(mka), kd(mkd), ks(mks), mirror(mmirror), g(mg) {};
        virtual ~BlinnPhongMaterial() = default;

        void scatter(Surfel* isec, Ray* r);
    };
}

#endif