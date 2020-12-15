#include "directional_light.hpp"

namespace rt3 {
    rgb DirectionalLight::sample_Li(Surfel* hit, const Vector3& wi, VisibilityTester* vis) {
        return rgb(0, 0, 0);
    }

    void DirectionalLight::preprocess(const Scene&) {

    }
}