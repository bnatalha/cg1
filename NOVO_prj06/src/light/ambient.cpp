#include "ambient.hpp"

namespace rt3 {
    rgb AmbientLight::sample_Li(Surfel* hit, const Vector3& wi, VisibilityTester* vis) {
        rgb(0,0,0);
    }

    void AmbientLight::preprocess(const Scene&) {

    }
}