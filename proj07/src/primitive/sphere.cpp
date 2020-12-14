#include "sphere.hpp"

namespace rt3 {

    Point3 Sphere::world_bounds() const { throw std::logic_error("not implemented"); }
    bool Sphere::bounding_box(float t0, float t1, aabb& box) const {
        box = aabb(c - Vector3(r, r, r), c + Vector3(r, r, r));
        return true;
    }


    bool Sphere::intersect(const Ray& ray, float& t_min, float& t_max, Surfel* sf) const {

        float A = dot(ray.d, ray.d);
        float B = dot(2.f * (ray.o - c), ray.d);
        float C = dot((ray.o - c), (ray.o - c)) - (r * r);
        float delta = B * B - 4.f * A * C;


        float t;
        if (delta >= 0.f) {
            if (delta == 0.f) {
                t = (-B) / (2.f * A);
            }
            else {
                float x1 = (-B + sqrt(delta)) / (2.f * A);
                float x2 = (-B - sqrt(delta)) / (2.f * A);
                t = x1 < x2 ? x1 : x2;

                // Vector3 oc = ray.o - c;
                // float p1 = dot(oc, ray.d);
                // float r1 = dot(oc, ray.d) * dot(oc, ray.d);
                // float r2 = dot(ray.d, ray.d) * dot(oc,  oc) - (r * r);

                // float t1 = (-p1 + sqrt(r1 - r2))/dot(ray.d, ray.d);
                // float t2 = (-p1 - sqrt(r1 - r2))/dot(ray.d, ray.d);

                // *t_hit = t1 < t2 ? t1 : t2;
            }

            if (t >= ray.t_min && t <= ray.t_max) {

                // if ((ray.t_max <= 0.f || t <= ray.t_max)) {

                ray.t_max = t;
                sf->t = t;
                sf->p = ray(t);

                Vector3 n = sf->p - c;
                // Vector3 n = 2.f * (sf->p - c);
                sf->n = normalize(n);

                return true;

            }
        }
        return false;


    }

    bool Sphere::intersect_p(const Ray& ray, float& hit1, float& hit2) const {

        aabb box;
        bounding_box(0.f, 1.f, box);
        return (box.intersect_p(ray, ray.t_min, ray.t_max));

        // float A = dot(ray.d, ray.d);
        // float B = dot(2.f * (ray.o - c), ray.d);
        // float C = dot((ray.o - c), (ray.o - c)) - (r * r);
        // float delta = B * B - 4.f * A * C;
        // // return delta >= 0.f;

        // float t = 0.f;

        // if (delta >= 0.f) {
        //     if (delta == 0.f) {
        //         t = (-B) / (2.f * A);
        //     }
        //     else if (delta > 0.f) {
        //         float x1 = (-B + sqrt(delta)) / (2.f * A);
        //         float x2 = (-B - sqrt(delta)) / (2.f * A);
        //         t = x1 < x2 ? x1 : x2;

        //         // Vector3 oc = ray.o - c;
        //         // float p1 = dot(oc, ray.d);
        //         // float r1 = dot(oc, ray.d) * dot(oc, ray.d);
        //         // float r2 = dot(ray.d, ray.d) * dot(oc,  oc) - (r * r);

        //         // float t1 = (-p1 + sqrt(r1 - r2))/dot(ray.d, ray.d);
        //         // float t2 = (-p1 - sqrt(r1 - r2))/dot(ray.d, ray.d);

        //         // t = t1 < t2 ? t1 : t2;
        //     }

        //     if (t >= ray.t_min && t <= ray.t_max) {
        //         return true;
        //     }
        // }
        // return false;
    }

    void Sphere::print() {
        // Shape::print();
        std::cout << "radius: " << r << " center: [" << c << "]\n";
    }

}