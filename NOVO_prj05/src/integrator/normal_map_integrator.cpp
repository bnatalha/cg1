#include "normal_map_integrator.hpp"

namespace rt3 {

    Point3 NormalMapIntegrator::Li(const Ray& ray, const Scene& scene, Point3 bkg_color) const {
        // Point3 L(255, 255, 255);
        Point3 L(bkg_color);

        std::shared_ptr<Surfel> isect = std::make_shared<Surfel>();
        if (scene.intersect(ray, isect.get())) {

            Vector3 normal = normalize(isect.get()->n);
            normal = normal + Vector3(1.f, 1.f, 1.f) * 0.5f;
            normal[0] = std::clamp(normal[0], 0.f, 1.f);
            normal[1] = std::clamp(normal[1], 0.f, 1.f);
            normal[2] = std::clamp(normal[2], 0.f, 1.f);

            L = rgb(255, 255, 255) * normal;
        }

        return L;
    }

    void NormalMapIntegrator::render(const Scene& scene) {
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
            if (j % (h / 10) == 0) {
                progressbar(j / (h / 10), "rendering...");
            }
        }
    }
    void NormalMapIntegrator::preprocess(const Scene& scene) {}
}