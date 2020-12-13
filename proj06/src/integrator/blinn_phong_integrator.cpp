#include "blinn_phong_integrator.hpp"

namespace rt3 {

    // [0] FIRST STEP TO INITIATE `L` WITH THE COLOR VALUE TO BE RETURNED.
    // [1] FIND CLOSEST RAY INTERSECTION OR RETURN BACKGROUND RADIANCE
    // [2] SPECIAL SITUATION: IF THE RAY HITS THE SURFACE FROM "BEHIND" (INSIDE), WE DO NOT COLOR.
    // [3] GET THE MATERIAL ASSOCIATED WITH THE HIT SURFACE
    // [4] INITIALIZE COMMON VARIABLES FOR BLINNPHONG INTEGRATOR (COEFFICIENTS AND VECTORS L, N, V, ETC.)
    // [5] CALCULATE & ADD CONTRIBUTION FROM EACH LIGHT SOURCE
    // [6] ADD AMBIENT CONTRIBUTION HERE (if there is any).
    // [7] ADD MIRROR REFLECTION CONTRIBUTION
    Point3 BlinnPhongIntegrator::Li(const Ray& ray, const Scene& scene, Point3 bkg_color, int depth) const {
        Point3 L;

        std::shared_ptr<Surfel> isect = std::make_shared<Surfel>();
        if (!scene.intersect(ray, isect.get())) {
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

                    Vector3 v = normalize(ray.o - P);
                    Vector3 h = (v + l) / (v + l).length();
                    Vector3 specular = bm->ks * I * pow(dot(n, h), bm->g);
                    L += specular;
                    // Ray shadowRay = Ray(wi, nP, epsilon, 1.f);

                    // // WIP: hard shadow
                    // // float epsilon = 0.0f;
                    // float epsilon = 0.08f;
                    // auto nP = Vector3(P[0] + epsilon, P[1] + epsilon, P[2] + epsilon);
                    // Vector3 wi = pointLight->from - nP;
                    // // Vector3 wi = normalize(pointLight->from - nP);

                    // Ray shadowRay = Ray(wi, nP);
                    // shadowRay.t_max = 1.f;
                    // // shadowRay.t_min = epsilon;
                    // shadowRay.t_min = 0.0f;

                    // if (scene.intersect_p(shadowRay))
                    // {
                    //     // L = Vector3(0.f, 0.f, 0.f);
                    //     L = ambient;
                    // }

                    // // // WIP: hard shadow
                    // // float epsilon = 0.08f;
                    // // // auto nP = Vector3(P[0] + epsilon, P[1] + epsilon, P[2] + epsilon);
                    // // auto nP = P;
                    // // Vector3 wi = normalize(pointLight->from - nP);
                    // // // Vector3 wi = pointLight->from - nP;
                    // // Ray shadowRay = Ray(wi, nP, .9f, 1.f);
                    // // // Ray shadowRay = Ray(wi, nP, epsilon, 1.f);
                }

                if (light->flags == light_flag_e::directional) {

                    DirectionalLight* directLight = dynamic_cast<DirectionalLight*>(light.get());

                    Vector3 I = directLight->scale * directLight->L;
                    Vector3 l = normalize(directLight->from - directLight->to);

                    Vector3 difuse = bm->kd * I * std::max(0.f, dot(n, l));
                    L += difuse;

                    Vector3 v = normalize(ray.o - P);
                    Vector3 h = (v + l) / (v + l).length();
                    Vector3 specular = bm->ks * I * pow(dot(n, h), bm->g);
                    L += specular;

                    // float epsilon = 0.08f;
                    // auto nP = Vector3(P[0] + epsilon, P[1] + epsilon, P[2] + epsilon);
                    // Vector3 wi = normalize(directLight->from - nP);
                    // Ray shadowRay = Ray(wi, nP, epsilon, 1.f);

                    // // // WIP: hard shadow
                    // // float epsilon = 0.08f;
                    // // // auto nP = Vector3(P[0] + epsilon, P[1] + epsilon, P[2] + epsilon);
                    // // auto nP = P;
                    // // Vector3 wi = normalize(pointLight->from - nP);
                    // // // Vector3 wi = pointLight->from - nP;
                    // // Ray shadowRay = Ray(wi, nP, .9f, 1.f);
                    // // // Ray shadowRay = Ray(wi, nP, epsilon, 1.f);

                    // if (scene.intersect_p(shadowRay))
                    // {
                    //     L = Vector3(0.f, 0.f, 0.f);
                    // }
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




            // Mirror

            // [1] Determine color L based on the Blinn-Phong model
            // [2] Find new ray, based on perfect reflection about surface normal.
            Ray reflected_ray = Ray(P, ray.d - 2 * (dot(ray.d, n)) * n);
            // [3] Offset reflect_ray by an epsilon, to avoid self-intersection caused by rounding error.
            // Vector3 epsilon = Vector3(1.f, 1.f, 1.f) + n;
            // reflected_ray.o = epsilon + reflected_ray.o;

            // [4] Recursive call of Li() with new reflected ray.
            if (depth < max_depth)
                L = L + bm->mirror * Li(reflected_ray, scene, bkg_color, depth + 1);


            L[0] = std::clamp(L[0], 0.f, 1.f);
            L[1] = std::clamp(L[1], 0.f, 1.f);
            L[2] = std::clamp(L[2], 0.f, 1.f);
            return L + ambient;
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
            if (j == h - 1) {
                progressbar_finish();
            }
            if (j % (h / 10) == 0) {
                progressbar(j / (h / 10), "rendering...");
            }
        }
    }
    void BlinnPhongIntegrator::preprocess(const Scene& scene) {
    }
}