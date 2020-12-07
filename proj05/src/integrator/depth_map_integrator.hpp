#ifndef DEPTH_MAP_INTEGRATOR_HPP
#define DEPTH_MAP_INTEGRATOR_HPP

#include <climits>
#include <limits>

#include "core/integrator.hpp"
#include "primitive/prim_list.hpp"
#include "primitive/flat_material.hpp"
#include "core/surfel.hpp"
#include "external/progress_bar.hpp"

namespace rt3 {
    class DepthMapIntegrator : public Integrator {

    public:
        DepthMapIntegrator(std::shared_ptr<Camera> cam, const float& z_min, const float& z_max, const rgb& nc, const rgb& fc);
        virtual ~DepthMapIntegrator() = default;

        float zmin;
        float zmax;
        rgb near_color;
        rgb far_color;
        std::shared_ptr<std::vector<float>> z_buffer;

        Point3 Li(const Ray& ray, const Scene& scene, Point3 bkg_color) const;
        void render(const Scene& scene);
        void preprocess(const Scene& scene);

        void add_z_point(Point2 p, float val);


    };
}

#endif