#ifndef GEOMETRIC_PRIMITIVE_HPP
#define GEOMETRIC_PRIMITIVE_HPP

#include "core/primitive.hpp"
#include "core/aabb.hpp"
#include "material.hpp"
#include "shape.hpp"

namespace rt3 {

    class GeometricPrimitive : public Primitive {
    public:
        std::shared_ptr<Material> material;
        std::shared_ptr<Shape> shape;

        GeometricPrimitive(std::shared_ptr<Material> material,
            std::shared_ptr<Shape> shape) : material(material), shape(shape) {}
        virtual ~GeometricPrimitive() = default;

        Point3 world_bounds() const;
        bool bounding_box(float t0, float t1, aabb& box) const;
        bool intersect(const Ray& ray, float& t_min, float& t_max, Surfel* sf) const;
        bool intersect_p(const Ray& ray, float& hit1, float& hit2) const;
        const Material* get_material(void) const;
        const void set_material(std::shared_ptr<Material> m);

        void print();
    };

}

#endif