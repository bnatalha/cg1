#include "visibility_tester.hpp"

namespace rt3 {
    VisibilityTester::VisibilityTester(const Surfel& s0, const Surfel& s1) {
        p0 = s0;
        p1 = p0;
    };

    bool VisibilityTester::unoccluded(const Scene& scene) { return true; }
}

