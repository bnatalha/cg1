#include "flat_integrator.hpp"

namespace rt3 {
    Point3 FlatIntegrator::Li(const Ray& ray, const Scene& scene, Point3 bkg_color) const {
        Point3 L(0, 0, 0);

        // Surfel isect;
        if (!scene.intersect_p(ray)) {
            L = bkg_color;
        }
        else {
            PrimList* pl = dynamic_cast<PrimList*>(scene.primitive.get());
            for (auto prim : pl->primitives) {
                if (prim->intersect_p(ray)) {
                    const FlatMaterial* fm = dynamic_cast<const FlatMaterial*>(prim->get_material());
                    L = fm->kd;
                }
            }
        }
        return L;

    }
    void FlatIntegrator::render(const Scene& scene) {
        auto w = camera->film.width;
        auto h = camera->film.height;
        // for ( int j = h-1 ; j >= 0 ; j-- ) {
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {

                // ------------ prj02 ---------------------------------------------
                // Ray ray = m_camera->generate_ray(i, j);

                // std::cout << "Pixel: [" << i << ", " << j <<"] "
                //         << "Ray [" << ray << "]" << std::endl;


                // auto color = m_scene->background.sample(float(i) / float(w), float(j) / float(h)); // get background color.
                // m_camera->film.add(Point2(i, j), color); // set image buffer at position (i,j), accordingly.

                // ------------ prj03 ---------------------------------------------
                Ray ray = camera->generate_ray(i, j);

                auto L_background = scene.background->sample(float(i) / float(w), float(j) / float(h)); // get background color.
                // for (auto p : m_scene->primitive) {
                //     if (p->intersect_p(ray)) {
                //         color = rgb(255, 0, 0); // hit objects with red
                //     }
                // }

                rgb L_color = Li(ray, scene, L_background);

                camera->film.add(Point2(i, j), L_color); // set image buffer at position (i,j).
            }
            if(j == h-1) {
                progressbar_finish();
            }
            if(j % (h/10) == 0) {
                progressbar(j/(h/10), "loading");
            }
        }
    }
    void FlatIntegrator::preprocess(const Scene& scene) {}
}