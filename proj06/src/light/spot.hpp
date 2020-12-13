#ifndef SPOT_LIGHT_HPP
#define SPOT_LIGHT_HPP

#include "core/light.hpp"

namespace rt3 {

    class SpotLight : public Light {
    public:
        Vector3 I;
        Vector3 scale;
        Vector3 from;
        Vector3 to;
        int cutoff;
        int falloff;

        SpotLight(Vector3 I, Vector3 scale, Vector3 from, Vector3 to, int& cutoff, int& falloff) : Light(light_flag_e::spot), I(I), scale(scale), from(from), to(to), cutoff(cutoff), falloff(falloff) {}
        // SpotLight(Vector3 from, Vector3 scale) : from(from), scale(scale) {};
        virtual ~SpotLight() = default;

        rgb sample_Li(Surfel* hit, const Vector3& wi, VisibilityTester* vis);

        void preprocess(const Scene&);

    };
}

#endif