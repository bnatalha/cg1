#include "geometric_primitive.hpp"

namespace rt3 {

    Point3 GeometricPrimitive::world_bounds() const { throw std::logic_error("not implemented"); }

    bool GeometricPrimitive::intersect(const Ray& ray, Surfel* sf) const {
        std::shared_ptr<float> hit_point = std::make_shared<float>(0);

        // return shape->intersect(ray, sf);
        if(shape->intersect(ray, hit_point.get(), sf)) {
            sf->primitive = this;
            return true;
        }
        return false;
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