#ifndef AMBIENT_LIGHT_HPP
#define AMBIENT_LIGHT_HPP

#include "core/light.hpp"

namespace rt3 {

    class AmbientLight : public Light {
    public:
        Vector3 L;
        Vector3 scale;

        AmbientLight(Vector3 L, Vector3 scale) : Light(light_flag_e::ambient), L(L), scale(scale) {}
        // AmbientLight(Vector3 from, Vector3 scale) : from(from), scale(scale) {};
        virtual ~AmbientLight() = default;

        rgb sample_Li(Surfel* hit, const Vector3& wi, VisibilityTester* vis);

        void preprocess(const Scene&);

    };
}

#endif