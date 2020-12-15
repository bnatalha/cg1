#include "spot.hpp"

namespace rt3 {
    rgb SpotLight::sample_Li(Surfel* hit, const Vector3& wi, VisibilityTester* vis) {
        rgb(0,0,0);
    }

    void SpotLight::preprocess(const Scene&) {

    }
}