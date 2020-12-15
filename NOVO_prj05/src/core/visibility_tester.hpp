#ifndef VISIBILITY_TESTER_HPP
#define VISIBILITY_TESTER_HPP

#include "core/surfel.hpp"

namespace rt3 {

    class Scene;

    // Verifica se há oclusão entre dois pontos de contato.
    class VisibilityTester
    {
    public:
        Surfel p0, p1;

        VisibilityTester() {}
        VisibilityTester(const Surfel&, const Surfel&);
        ~VisibilityTester();

        bool unoccluded(const Scene& scene);
    };
}

#include "core/scene.hpp"

#endif