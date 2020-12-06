#ifndef SURFEL_HPP
#define SURFEL_HPP

#include <forward_list>
#include <memory>

#include "primitive.hpp"
#include "ray.hpp"
#include "vector3.hpp"


namespace rt3 {
    class Primitive;

    class Surfel {
    public:
        Surfel() {};
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

}


#endif