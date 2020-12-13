#include "depth_map_integrator.hpp"

namespace rt3 {

    DepthMapIntegrator::DepthMapIntegrator(std::shared_ptr<Camera> cam, const float& z_min, const float& z_max, const rgb& nc, const rgb& fc)
        : Integrator(cam)
        // zmin{ zmin },
        // zmax{ zmax },
        // near_color{ nc },
        // far_color{ fc },
    {
        zmin = z_min;
        zmax = z_max;
        near_color = nc;
        far_color = fc;
    }


    Point3 DepthMapIntegrator::Li(const Ray& ray, const Scene& scene, Point3 bkg_color) const {
        Point3 L(far_color);

        std::shared_ptr<Surfel> isect = std::make_shared<Surfel>();
        if (scene.intersect(ray, isect.get())) {

            // rgb kd = rgb(255.f, 0.f, 0.f);    // default red material
            float z = isect.get()->p[0];
            float d = std::abs(zmax - zmin);
            float perc = (zmax - z)/d;

            L[0] = std::abs(far_color[0] - near_color[0]) * perc;
            L[1] = std::abs(far_color[1] - near_color[1]) * perc;
            L[2] = std::abs(far_color[2] - near_color[2]) * perc;

            
        }
        return L;

    }
    void DepthMapIntegrator::render(const Scene& scene) {
        // preprocess(scene);

        auto w = camera->film.width;
        auto h = camera->film.height;
        // for ( int j = h-1 ; j >= 0 ; j-- ) {
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                Ray ray = camera->generate_ray(i, j);

                auto L_background = scene.background->sample(float(i) / float(w), float(j) / float(h)); // get background color.

                rgb L_color = Li(ray, scene, L_background);

                camera->film.add(Point2(i, j), L_color); // set image buffer at position (i,j).
            }
            if (j == h - 1) {
                progressbar_finish();
            }
            if (j % (h / 10) == 0) {
                progressbar(j / (h / 10), "loading");
            }
        }
    }
    void DepthMapIntegrator::preprocess(const Scene& scene) {
        // std::cout << "zmin " << zmin <<  std::endl;
        // std::cout << "zmax " << zmax <<  std::endl;
        // std::cout << "near_color " << near_color <<  std::endl;
        // std::cout << "far_color " << far_color <<  std::endl;

        auto w = camera->film.width;
        auto h = camera->film.height;
        z_buffer = std::make_shared<std::vector<float>>(w*h);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                Ray ray = camera->generate_ray(i, j);

                std::shared_ptr<Surfel> isect = std::make_shared<Surfel>();
                if (scene.intersect(ray, isect.get())) {
                    float z = isect.get()->p[0];
                    add_z_point(Point2(i, j), z);
                    zmin = z < zmin ? z : zmin;
                    zmax = z > zmax ? z : zmax;
                    continue;
                }
                add_z_point(Point2(i, j), std::numeric_limits<float>::max()); // set image buffer at position (i,j).
            }
        }


    }

    void DepthMapIntegrator::add_z_point(Point2 p, float val) {
        (*z_buffer)[p.first + (camera->film.width * p.second)] = val;
    }
}