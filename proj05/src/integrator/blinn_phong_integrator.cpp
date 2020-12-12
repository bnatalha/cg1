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

            Vector3 n = isect.get()->n;
            Point3 P = isect->p;

            const BlinnPhongMaterial* bm = dynamic_cast<const BlinnPhongMaterial*>(isect.get()->primitive->get_material());
            for (auto light : scene.lights) {

                PointLight* pointLight = dynamic_cast<PointLight*>(light.get());
                if (pointLight != nullptr) {

                    Vector3 l = normalize(pointLight->from - P);
                    Vector3 I = pointLight->scale * pointLight->I;

                    Vector3 difuse = bm->kd * I * std::max(0.f, dot(n, l));
                    L += difuse;

                    Vector3 v = (ray.o - P);
                    Vector3 h = normalize(l + v);
                    Vector3 specular = bm->ks * I * pow(std::max(0.f, dot(n, h)), bm->g);
                    L += specular;
                }

                DirectionalLight* directLight = dynamic_cast<DirectionalLight*>(light.get());
                if (directLight != nullptr) {

                    Vector3 I = directLight->scale * directLight->L;
                    Vector3 l = normalize(directLight->from - directLight->to);

                    Vector3 difuse = bm->kd * I * std::max(0.f, dot(n, l));
                    L += difuse;

                    Vector3 v = (P - ray.o);
                    Vector3 h = normalize(l + v);
                    Vector3 specular = bm->ks * I * pow(std::max(0.f, dot(n, h)), bm->g);
                    L += specular;

                    // // WIP: hard shadow
                    // float epsilon = 0.05;
                    // Vector3 wi = directLight->from - P;
                    // Ray shadowRay = Ray(wi, P, 1.f, 0.f);
                    // if (scene.intersect_p(shadowRay))
                    // {
                    //     L = Vector3(0.f, 0.f, 0.f);
                    // }
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
            return L;
        }
    }

    void BlinnPhongIntegrator::render(const Scene& scene) {
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
                progressbar(j / (h / 10), "loading");
            }
        }
    }
    void BlinnPhongIntegrator::preprocess(const Scene& scene) {
    }
}