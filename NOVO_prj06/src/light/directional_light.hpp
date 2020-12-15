#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "core/light.hpp"

namespace rt3 {

    class DirectionalLight : public Light {
    public:
        Vector3 L;
        Vector3 scale;
        Vector3 from;
        Vector3 to;

        DirectionalLight(Vector3 L, Vector3 scale, Vector3 from, Vector3 to) : Light(light_flag_e::directional), L(L), scale(scale), from(from), to(to) {}
        // DirectionalLight(Vector3 from, Vector3 scale) : from(from), scale(scale) {};
        virtual ~DirectionalLight() = default;

        rgb sample_Li(Surfel* hit, const Vector3& wi, VisibilityTester* vis);
        void preprocess(const Scene&);

    };
}

#endif