#include "blinn_phong_integrator.hpp"

namespace rt3 {

    Point3 BlinnPhongIntegrator::Li(const Ray& ray, const Scene& scene, Point3 bkg_color, int depth) const {
        Point3 L;
        Ray r = ray;

        float hit1 = 0, hit2 = 0;
        std::shared_ptr<Surfel> isect = std::make_shared<Surfel>();
        if (!scene.intersect(ray, ray.t_min, ray.t_max, isect.get())) {
            return bkg_color;
        }
        else {

            L = Vector3(0.f, 0.f, 0.f);

            Vector3 n = isect->n;
            Point3 P = isect->p;
            auto ambient = Vector3(0.f, 0.f, 0.f);

            const BlinnPhongMaterial* bm = dynamic_cast<const BlinnPhongMaterial*>(isect.get()->primitive->get_material());
            for (auto light : scene.lights) {
                if (light->flags == light_flag_e::ambient) {
                    AmbientLight* ambLight = dynamic_cast<AmbientLight*>(light.get());

                    Vector3 I = ambLight->L * ambLight->scale;
                    ambient += bm->ka * I;
                }

                if (light->flags == light_flag_e::point) {

                    PointLight* pointLight = dynamic_cast<PointLight*>(light.get());

                    Vector3 l = normalize(pointLight->from - P);
                    Vector3 I = pointLight->scale * pointLight->I;

                    Vector3 difuse = bm->kd * I * std::max(0.f, dot(n, l));
                    L += difuse;

                    Vector3 v = normalize(r.o - P);
                    Vector3 h = (v + l) / (v + l).length();
                    Vector3 specular = bm->ks * I * pow(dot(n, h), bm->g);
                    L += specular;

                    constexpr float epsilon = 0.005f;
                    Vector3 eps{ epsilon,epsilon,epsilon };
                    Ray shadow_ray(P, pointLight->from - P, (0.f + epsilon), 1.f);

                    if (scene.intersect_p(shadow_ray, shadow_ray.t_min, shadow_ray.t_max)) {
                        L = bm->ka * I;
                    }
                }

                if (light->flags == light_flag_e::directional) {

                    DirectionalLight* directLight = dynamic_cast<DirectionalLight*>(light.get());

                    Vector3 I = directLight->scale * directLight->L;
                    Vector3 l = normalize(directLight->from - directLight->to);

                    Vector3 difuse = bm->kd * I * std::max(0.f, dot(n, l));
                    L += difuse;

                    Vector3 v = normalize(r.o - P);
                    Vector3 h = (v + l) / (v + l).length();
                    Vector3 specular = bm->ks * I * pow(dot(n, h), bm->g);
                    L += specular;
                }

                if (light->flags == light_flag_e::spot) {

                    SpotLight* spotLight = dynamic_cast<SpotLight*>(light.get());

                    Vector3 I = spotLight->L * spotLight->scale;
                    Vector3 spotDir = normalize(spotLight->from - spotLight->to);
                    Vector3 pFromSpot = normalize(spotLight->from - P);

                    // float pCos = dot(pFromSpot, spotDir);
                    float pCos = std::abs(dot(pFromSpot, spotDir));
                    float cutoff = TO_RADIANS(spotLight->cutoff);
                    float cutoffCos = cos(cutoff);

                    // if (!(0.8f <= cosAngle && cosAngle <= 1.f))
                    if (pCos > 10.f) {
                        Vector3 l = pFromSpot;

                        Vector3 difuse = bm->kd * I * std::max(0.f, dot(n, l));
                        L += difuse;
                    }
                    else {
                        continue;
                    }
                }
            }

            // // Mirror

            // // [1] Determine color L based on the Blinn-Phong model
            // // [2] Find new ray, based on perfect reflection about surface normal.
            Ray reflected_ray = Ray(P, r.d - 2 * (dot(r.d, n)) * n);
            // // [3] Offset reflect_ray by an epsilon, to avoid self-intersection caused by rounding error.
            // Vector3 epsilon = Vector3(1.f, 1.f, 1.f) + n;
            // reflected_ray.o = epsilon + reflected_ray.o;

            // // [4] Recursive call of Li() with new reflected ray.
            if (depth < max_depth) {
                L = L + bm->mirror * Li(reflected_ray, scene, bkg_color, depth + 1);
            }

            L += ambient;

            L[0] = std::clamp(L[0], 0.f, 1.f);
            L[1] = std::clamp(L[1], 0.f, 1.f);
            L[2] = std::clamp(L[2], 0.f, 1.f);

            return L;
        }

    }

    void BlinnPhongIntegrator::render(const Scene& scene) {
        std::cout << camera->film.filename << "\n";
        auto w = camera->film.width;
        auto h = camera->film.height;
        // for ( int j = h-1 ; j >= 0 ; j-- ) {
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                Ray ray = camera->generate_ray(i, j);

                auto L_background = scene.background->sample(float(i) / float(w), float(j) / float(h));
                L_background = L_background / 255.f; // get background color.

                rgb L_color = 255 * Li(ray, scene, L_background, 0);

                camera->film.add(Point2(i, j), L_color); // set image buffer at position (i,j).
            }
            if (j % (h / 10) == 0) {
                progressbar(j / (h / 10), "rendering...");
            }
        }
    }

    void BlinnPhongIntegrator::preprocess(const Scene& scene) {
    }
}