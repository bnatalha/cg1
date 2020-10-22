#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <forward_list>
// #include <memory>

#include "ray.hpp"
#include "vector3.hpp"


namespace rt3 {
    class Primitive;

    class Surfel {
    public:
        Surfel(const Point3& p, const Vector3& n, const Vector3& wo, float time,
            const Point2& uv, const Primitive* pri)
            : p{ p }, n{ n }, wo{ wo }, time{ time }, uv{ uv }, primitive{ pri }
        {/* empty */};

        Point3 p;        //!< Contact point.
        Vector3 n;       //!< The surface normal.
        Vector3 wo;      //!< Outgoing direction of light, which is -ray.
        float time;     //!< Time of contact.
        Point2 uv;     //!< Parametric coordinate (u,v) of the hit surface.
        const Primitive* primitive = nullptr; //!< Pointer to the primitive.
    };


    class Primitive {
    public:
        std::string type;

        Primitive(string type) : type(type) {}
        virtual ~Primitive() {};

        virtual bool intersect(const Ray& ray, Surfel* sf) const = 0;
        // Simpler & faster version of intersection that only return true/false.
        // It does not compute the hit point information.
        virtual bool intersect_p(const Ray& ray) const = 0;
        virtual void print() {
            std::cout << "type: " << type << std::endl;
        };
        //     virtual const Material* get_material(void) const = { return material; }
        // private:
        //     std::shared_ptr<Material> material;
    };

    class Sphere : public Primitive {
    public:
        float r;
        Point3 c;

        Sphere(string type, float r, Point3 c) : Primitive(type), r(r), c(c) {}
        virtual ~Sphere() = default;

        inline bool intersect(const Ray& ray, Surfel* sf) const { return false; }
        inline bool intersect_p(const Ray& ray) const {
             float A = dot(ray.d, ray.d);
             float B = dot(2 * (ray.o - c), ray.d);
             float C = dot((ray.o - c), (ray.o - c) )- (r * r);
             float delta = B * B - 4 * A * C;
             return delta >= 0;
        }

        inline void print() {
            Primitive::print();
            std::cout << "radius: " << r << " center: [" << c << "]\n";
        }
    };

    typedef std::forward_list<std::shared_ptr<Primitive>> ObjectList;
}


#endif