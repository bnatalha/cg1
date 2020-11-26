#ifndef FLAT_INTEGRATOR_HPP
#define FLAT_INTEGRATOR_HPP

#include "core/integrator.hpp"
#include "primitive/prim_list.hpp"
#include "primitive/flat_material.hpp"
#include "core/surfel.hpp"
#include "external/progress_bar.hpp"

namespace rt3 {
    class FlatIntegrator : public Integrator {

    public:
        FlatIntegrator(std::shared_ptr<Camera> cam) : Integrator(cam) {}
        virtual ~FlatIntegrator() = default;

        Point3 Li(const Ray& ray, const Scene& scene, Point3 bkg_color) const;
        void render(const Scene& scene);
        void preprocess(const Scene& scene);

    };
}

#endif