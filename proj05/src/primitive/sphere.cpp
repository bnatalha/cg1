#include "sphere.hpp"

namespace rt3 {

    Point3 Sphere::world_bounds() const { throw std::logic_error("not implemented"); }

    bool Sphere::intersect(const Ray& ray, float* t_hit, Surfel* sf) const {
        float A = dot(ray.d, ray.d);
        float B = dot(2.f * (ray.o - c), ray.d);
        float C = dot((ray.o - c), (ray.o - c)) - (r * r);
        float delta = B * B - 4.f * A * C;


        if (delta >= 0.f) {
            if (delta == 0.f) {
                *t_hit = (-B) / (2.f * A);
            }
            else if (delta > 0.f) {
                float x1 = (-B + sqrt(delta)) / (2.f * A);
                float x2 = (-B - sqrt(delta)) / (2.f * A);
                *t_hit = x1 < x2 ? x1 : x2;

                // Vector3 oc = ray.o - c;
                // float p1 = dot(oc, ray.d);
                // float r1 = dot(oc, ray.d) * dot(oc, ray.d);
                // float r2 = dot(ray.d, ray.d) * dot(oc,  oc) - (r * r);

                // float t1 = (-p1 + sqrt(r1 - r2))/dot(ray.d, ray.d);
                // float t2 = (-p1 - sqrt(r1 - r2))/dot(ray.d, ray.d);

                // *t_hit = t1 < t2 ? t1 : t2;
            }

            if ((*t_hit) > ray.t_min) {

                if ((ray.t_max <= 0.f || *(t_hit) < ray.t_max)) {

                    ray.t_max = *(t_hit);

                    sf->p = ray(*t_hit);
                    // sf->n = 2 * (sf->p - c) / r;
                    // sf->wo = (sf->p - c) / r;

                    // sf->n = normalize(sf->p - c);

                    // sf->n = normalize((sf->p - ray.o));


                    // sf->n = normalize(2.f * (sf->p - c));
                    Vector3 n = normalize(2.f * (sf->p - c));
                    sf->n = n;
                    // sf->n = dot(sf->n, ray.d) < 0 ? (-1* n) : n;
                    // sf->wo = dot(ray.d, sf->n) < 0 ? -1 * (sf->n) : sf->n;

                    return true;

                }
            }
        }
        return false;


    }

    bool Sphere::intersect_p(const Ray& ray) const {
        float A = dot(ray.d, ray.d);
        float B = dot(2.f * (ray.o - c), ray.d);
        float C = dot((ray.o - c), (ray.o - c)) - (r * r);
        float delta = B * B - 4.f * A * C;
        // return delta >= 0.f;

        float t_hit = 0.f;

        if (delta >= 0.f) {
            if (delta == 0.f) {
                t_hit = (-B) / (2.f * A);
            }
            else if (delta > 0.f) {
                float x1 = (-B + sqrt(delta)) / (2.f * A);
                float x2 = (-B - sqrt(delta)) / (2.f * A);
                t_hit = x1 < x2 ? x1 : x2;

                // Vector3 oc = ray.o - c;
                // float p1 = dot(oc, ray.d);
                // float r1 = dot(oc, ray.d) * dot(oc, ray.d);
                // float r2 = dot(ray.d, ray.d) * dot(oc,  oc) - (r * r);

                // float t1 = (-p1 + sqrt(r1 - r2))/dot(ray.d, ray.d);
                // float t2 = (-p1 - sqrt(r1 - r2))/dot(ray.d, ray.d);

                // *t_hit = t1 < t2 ? t1 : t2;
            }

            if (t_hit > ray.t_min) {

                if ((ray.t_max <= 0.f || t_hit < ray.t_max)) {

                    return true;

                }
            }
        }
        return false;
    }

    void Sphere::print() {
        // Shape::print();
        std::cout << "radius: " << r << " center: [" << c << "]\n";
    }

}