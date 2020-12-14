#ifndef AABB_HPP
#define AABB_HPP
//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "vector3.hpp"
#include "ray.hpp"

float ffmin(float a, float b);
float ffmax(float a, float b);

namespace rt3 {

    class aabb {
    public:
        aabb() {}
        aabb(const Point3& a, const Point3& b) { minimum = a; maximum = b; }

        Point3 min() const { return minimum; }
        Point3 max() const { return maximum; }

        bool intersect_p(const Ray& r, float& t_min, float& t_max) const;

        double area() const;

        int longest_axis() const;

    public:
        Point3 minimum;
        Point3 maximum;
    };

    aabb surrounding_box(aabb box0, aabb box1);
}


#endif
