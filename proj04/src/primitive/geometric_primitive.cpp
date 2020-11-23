#include "geometric_primitive.hpp"

namespace rt3 {

    Point3 GeometricPrimitive::world_bounds() const {throw std::logic_error("not implemented");}

    bool GeometricPrimitive::intersect(const Ray& ray, Surfel* sf) const {
        float* hit_point;
        return shape->intersect(ray, hit_point, sf);
    }

    bool GeometricPrimitive::intersect_p(const Ray& ray) const {
        return shape->intersect_p(ray);
    }

    const Material* GeometricPrimitive::get_material(void) const {
        return material.get();
    }

    const void GeometricPrimitive::set_material(std::shared_ptr<Material> m) {
        material = std::move(m);
    }

    void GeometricPrimitive::print() {};
}