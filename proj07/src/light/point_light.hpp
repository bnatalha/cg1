#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "core/light.hpp"

namespace rt3 {

    class PointLight : public Light {
    public:
        Vector3 I;
        Vector3 scale;
        Vector3 from;

        PointLight(Vector3 I, Vector3 scale, Vector3 from) : Light(light_flag_e::point), I(I), scale(scale), from(from){}
        // PointLight(Vector3 from, Vector3 scale) : from(from), scale(scale) {};
        virtual ~PointLight() = default;

        rgb sample_Li(Surfel* hit, const Vector3& wi, VisibilityTester* vis);

        void preprocess(const Scene&);

    };
}

#endif