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

#include "aabb.hpp"

float ffmin(float a, float b) { return a < b ? a : b; }
float ffmax(float a, float b) { return a > b ? a : b; }

namespace rt3 {

    bool aabb::intersect_p(const Ray& r, float& t_min, float& t_max) const {
        for (int a = 0; a < 3; a++) {
            auto t0 = ffmin((minimum[a] - r.o[a]) / r.d[a],
                (maximum[a] - r.o[a]) / r.d[a]);
            auto t1 = ffmax((minimum[a] - r.o[a]) / r.d[a],
                (maximum[a] - r.o[a]) / r.d[a]);
            t_min = ffmax(t0, t_min);
            t_max = ffmin(t1, t_max);

            r.t_min = t_min;
            r.t_max = t_max;

            if (t_max < t_min)
                return false;
        }
        return true;
    }

    double aabb::area() const {
        auto a = maximum.x() - minimum.x();
        auto b = maximum.y() - minimum.y();
        auto c = maximum.z() - minimum.z();
        return 2 * (a * b + b * c + c * a);
    }

    int aabb::longest_axis() const {
        auto a = maximum.x() - minimum.x();
        auto b = maximum.y() - minimum.y();
        auto c = maximum.z() - minimum.z();
        if (a > b && a > c)
            return 0;
        else if (b > c)
            return 1;
        else
            return 2;
    }


    aabb surrounding_box(aabb box0, aabb box1) {
        Point3 small(ffmin(box0.min().x(), box1.min().x()),
            ffmin(box0.min().y(), box1.min().y()),
            ffmin(box0.min().z(), box1.min().z()));

        Point3 big(ffmax(box0.max().x(), box1.max().x()),
            ffmax(box0.max().y(), box1.max().y()),
            ffmax(box0.max().z(), box1.max().z()));

        return aabb(small, big);
    }
}
