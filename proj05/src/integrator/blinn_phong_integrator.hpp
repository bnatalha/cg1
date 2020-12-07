#ifndef BLINN_PHONG_INTEGRATOR_HPP
#define BLINN_PHONG_INTEGRATOR_HPP

#include "core/integrator.hpp"

namespace rt3 {
    class BlinnPhongIntegrator : public Integrator
    {
    public:
        BlinnPhongIntegrator(std::shared_ptr<Camera> cam) : Integrator(cam) {}
        virtual ~BlinnPhongIntegrator() = default;

        Point3 Li(const Ray& ray, const Scene& scene, Point3 bkg_color) const;
        void render(const Scene& scene);
        void preprocess(const Scene& scene);
    };


}

#endif