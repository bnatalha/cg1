#ifndef BLINN_PHONG_INTEGRATOR_HPP
#define BLINN_PHONG_INTEGRATOR_HPP

#include <algorithm>

#include "core/integrator.hpp"
#include "external/progress_bar.hpp"
#include "primitive/blinn_phong_material.hpp"

namespace rt3 {
    class BlinnPhongIntegrator : public Integrator
    {
    public:
        BlinnPhongIntegrator(std::shared_ptr<Camera> cam, float depth) : Integrator(cam), max_depth(depth) {}
        virtual ~BlinnPhongIntegrator() = default;
        // int depth;
        int max_depth;

        Point3 Li(const Ray& ray, const Scene& scene, Point3 bkg_color, int depth) const;
        Point3 Li(const Ray& ray, const Scene& scene, Point3 bkg_color) const { return Vector3(0, 0, 0); };
        void render(const Scene& scene);
        void preprocess(const Scene& scene);
    };


}

#endif