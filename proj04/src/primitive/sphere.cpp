#include "sphere.hpp"

namespace rt3 {

    Point3 Sphere::world_bounds() const { throw std::logic_error("not implemented"); }

    bool Sphere::intersect(const Ray& ray, float* t_hit, Surfel* sf) const { return false; }

    bool Sphere::intersect_p(const Ray& ray) const {
        float A = dot(ray.d, ray.d);
        float B = dot(2 * (ray.o - c), ray.d);
        float C = dot((ray.o - c), (ray.o - c)) - (r * r);
        float delta = B * B - 4 * A * C;
        return delta >= 0;
    }

    void Sphere::print() {
        // Shape::print();
        std::cout << "radius: " << r << " center: [" << c << "]\n";
    }

}