#include "flat_integrator.hpp"

namespace rt3 {
    Point3 FlatIntegrator::Li(const Ray& ray, const Scene& scene, Point3 bkg_color) const {
        Point3 L(bkg_color);

        float hit1=0, hit2 = 0;

        // std::shared_ptr<Surfel> isect = std::make_shared<Surfel>();
        // if (scene.intersect(ray, hit1, hit2, isect.get())) {
        //     Point3 light_pos(1.f, 3.f, 3.f);       // Point light location    (hardcoded here, for now)
        //     Vector3 light_I(0.9f, 0.9f, 0.9f); // Point light Intensity   (hardcoded here, for now)
        //     // rgb kd = rgb(255.f,0.f,0.f);    // default red material
        //     Vector3 l;                        // This is the light vector.
        //     l = light_pos - isect->p;           // Determine the vector from the light to the hit point `p`.
        //     l = normalize(l);

        //     const FlatMaterial* fm = dynamic_cast<const FlatMaterial*>(isect.get()->primitive->get_material());
        //     const BlinnPhongMaterial* bm = dynamic_cast<const BlinnPhongMaterial*>(isect.get()->primitive->get_material());
        //     if (fm != nullptr) {
        //         L = fm->kd * light_I * std::max(0.f, dot(isect->n, l));
        //     }
        //     else if (bm != nullptr) {
        //         L = bm->kd * light_I * std::max(0.f, dot(isect->n, l));
        //         L = L*255;
        //     }
        // }
        // return L;

        std::shared_ptr<Surfel> isect = std::make_shared<Surfel>();
        if (!scene.intersect(ray, ray.t_min, ray.t_max, isect.get())) {
        // if (!scene.intersect_p(ray, ray.t_min, ray.t_max)) {
            return L;
        }
        else {

            const BlinnPhongMaterial* bm = dynamic_cast<const BlinnPhongMaterial*>(isect.get()->primitive->get_material());
            L = bm->kd;

            // // constexpr float epsilon = 0.005f;
            // constexpr float epsilon = 0.005f;
            // Vector3 P{isect.get()->p};
            // Vector3 eps{ epsilon,epsilon,epsilon };
            // Vector3 light_from{0.1f, 3.f, 1.f};
            // Ray shadow_ray(P, light_from - P, (epsilon), 1.f);

            // if (scene.intersect_p(shadow_ray, shadow_ray.t_min, shadow_ray.t_max)) {
            //     L = Vector3(0.f,0.f,0.f);
            // }

            return 255.f * L;


            // return Vector3(255,50,40);

        }

    }
    void FlatIntegrator::render(const Scene& scene) {
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
                progressbar(j / (h / 10), "rendering");
            }
        }
    }
    void FlatIntegrator::preprocess(const Scene& scene) {}
}