#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include "scene.hpp"
#include "ray.hpp"
#include "camera.hpp"

namespace rt3 {

    class Integrator {
    public:
        std::shared_ptr<Camera> camera;

        Integrator(std::shared_ptr<Camera> cam) : camera(cam) {}
        virtual ~Integrator() {};
        
        virtual void render(const Scene& scene) = 0;
        // };

        // class SamplerIntegrator : public Integrator {
        // public:

        // virtual ~SamplerIntegrator();
        // SamplerIntegrator(std::shared_ptr<const Camera> cam) : camera(cam) {}

        virtual Point3 Li(const Ray& ray, const Scene& scene, Point3 bkg_color) const = 0;
        virtual Point3 Li(const Ray& ray, const Scene& scene, Point3 bkg_color, int depth) const = 0;
        // virtual void render(const Scene& scene);
        virtual void preprocess(const Scene& scene) = 0;

    };

}

#endif