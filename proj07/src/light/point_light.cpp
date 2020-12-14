#include "point_light.hpp"

namespace rt3 {
    rgb PointLight::sample_Li(Surfel* hit, const Vector3& wi, VisibilityTester* vis) {
        return rgb(0,0,0);
    }

    void PointLight::preprocess(const Scene&) {

    }
}