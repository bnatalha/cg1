#ifndef GEOMETRIC_PRIMITIVE_HPP
#define GEOMETRIC_PRIMITIVE_HPP

#include "core/primitive.hpp"
#include "material.hpp"
#include "shape.hpp"

namespace rt3 {

    class GeometricPrimitive : public Primitive {
    public:
        std::shared_ptr<Material> material;
        std::shared_ptr<Shape> shape;

        GeometricPrimitive(std::shared_ptr<Material> material,
        std::shared_ptr<Shape> shape) :  material(material), shape(shape) {}
        virtual ~GeometricPrimitive() = default;

        Point3 world_bounds() const;
        bool intersect(const Ray& ray, Surfel* sf) const;
        bool intersect_p(const Ray& ray) const;
        const Material* get_material(void) const;
        const void set_material(std::shared_ptr<Material> m);

        void print();
    };

}

#endif