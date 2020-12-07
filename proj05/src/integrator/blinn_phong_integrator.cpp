#include "blinn_phong_integrator.hpp"

namespace rt3 {
    Point3 BlinnPhongIntegrator::Li(const Ray& ray, const Scene& scene, Point3 bkg_color) const {
        return bkg_color;

        // [0] FIRST STEP TO INITIATE `L` WITH THE COLOR VALUE TO BE RETURNED.
        // [1] FIND CLOSEST RAY INTERSECTION OR RETURN BACKGROUND RADIANCE
        // [2] SPECIAL SITUATION: IF THE RAY HITS THE SURFACE FROM "BEHIND" (INSIDE), WE DO NOT COLOR.
        // [3] GET THE MATERIAL ASSOCIATED WITH THE HIT SURFACE
        // [4] INITIALIZE COMMON VARIABLES FOR BLINNPHONG INTEGRATOR (COEFFICIENTS AND VECTORS L, N, V, ETC.)
        // [5] CALCULATE & ADD CONTRIBUTION FROM EACH LIGHT SOURCE
        // [6] ADD AMBIENT CONTRIBUTION HERE (if there is any).
        // [7] ADD MIRROR REFLECTION CONTRIBUTION

        // return L;

    }
    void BlinnPhongIntegrator::render(const Scene& scene) {}
    void BlinnPhongIntegrator::preprocess(const Scene& scene) {}
}