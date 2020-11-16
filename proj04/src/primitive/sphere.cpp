#include "sphere.hpp"

namespace rt3 {

    bool Sphere::intersect(const Ray& ray, Surfel* sf) const { return false; }

    bool Sphere::intersect_p(const Ray& ray) const {
        float A = dot(ray.d, ray.d);
        float B = dot(2 * (ray.o - c), ray.d);
        float C = dot((ray.o - c), (ray.o - c)) - (r * r);
        float delta = B * B - 4 * A * C;
        return delta >= 0;
    }

    void Sphere::print() {
        Primitive::print();
        std::cout << "radius: " << r << " center: [" << c << "]\n";
    }

}