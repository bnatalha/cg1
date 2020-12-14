#include "geometric_primitive.hpp"

namespace rt3 {

    Point3 GeometricPrimitive::world_bounds() const { throw std::logic_error("not implemented"); }
    bool GeometricPrimitive::bounding_box(float t0, float t1, aabb& box) const { return shape->bounding_box(t0, t1, box); }

    bool GeometricPrimitive::intersect(const Ray& ray, float& t_min, float& t_max, Surfel* sf) const {
        // std::shared_ptr<float> hit_point = std::make_shared<float>(0);

        // if (shape->intersect(ray, hit_point.get(), sf)) {
        if (shape->intersect(ray, t_min, t_max, sf)) {
            sf->primitive = this;
            return true;
        }
        return false;
    }

    bool GeometricPrimitive::intersect_p(const Ray& ray, float& hit1, float& hit2) const{
        return shape->intersect_p(ray, hit1, hit2);
    }

    const Material* GeometricPrimitive::get_material(void) const {
        return material.get();
    }

    const void GeometricPrimitive::set_material(std::shared_ptr<Material> m) {
        material = std::move(m);
    }

    void GeometricPrimitive::print() {};
}