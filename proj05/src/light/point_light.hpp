#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "core/light.hpp"

namespace rt3 {

    class PointLight : public Light {
    public:
        Vector3 from;
        Vector3 scale;

        PointLight(Vector3 from, Vector3 scale) : Light(light_flag_e::point), from(from), scale(scale) {}
        // PointLight(Vector3 from, Vector3 scale) : from(from), scale(scale) {};
        virtual ~PointLight() = default;

        rgb sample_Li(const Surfel& hit, Vector3* wi, VisibilityTester* vis);
        void preprocess(const Scene&);

    };
}

#endif