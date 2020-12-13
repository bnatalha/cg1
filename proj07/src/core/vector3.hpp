#ifndef VECTOR3_HPP
#define VECTOR3_HPP
//==================================================================================================
// Written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <sstream>




class Vector3
{
public:
    Vector3() {}
    Vector3(float e0, float e1, float e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }
    Vector3(const Vector3& v)
    {
        e[0] = v.e[0];
        e[1] = v.e[1];
        e[2] = v.e[2];
    }
    Vector3(const char* str)
    {
        std::stringstream sstr;
        float a, b, c;
        sstr << str;
        sstr >> a >> b >> c;
        e[0] = a;
        e[1] = b;
        e[2] = c;
    }
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const Vector3& operator+() const { return *this; }
    inline Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    inline Vector3& operator+=(const Vector3& v2);
    inline Vector3& operator-=(const Vector3& v2);
    inline Vector3& operator*=(const Vector3& v2);
    inline Vector3& operator/=(const Vector3& v2);
    inline Vector3& operator*=(const float t);
    inline Vector3& operator/=(const float t);

    inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
    inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    inline void make_unit_vector();
    inline void normalize() { return make_unit_vector(); }

    float e[3];
};

inline Vector3 normalize(Vector3& v) {
    Vector3 n = Vector3(v);
    n.make_unit_vector();
    return n;
}

inline Vector3 normalize(const Vector3& v) {
    Vector3 n = Vector3(v);
    n.make_unit_vector();
    return n;
}

inline std::istream& operator>>(std::istream& is, Vector3& t)
{
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& t)
{
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline void Vector3::make_unit_vector()
{
    float k = 1.f / sqrt(std::pow(e[0], 2.0) + std::pow(e[1], 2.0) + std::pow(e[2], 2.0) );
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
    return Vector3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
    return Vector3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vector3 operator*(const Vector3& v1, const Vector3& v2)
{
    return Vector3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vector3 operator/(const Vector3& v1, const Vector3& v2)
{
    return Vector3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vector3 operator*(float t, const Vector3& v)
{
    return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vector3 operator/(Vector3 v, float t)
{
    return Vector3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline Vector3 operator*(const Vector3& v, float t)
{
    return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline float dot(const Vector3& v1, const Vector3& v2)
{
    return v1.e[0] * v2.e[0] + 
           v1.e[1] * v2.e[1] + 
           v1.e[2] * v2.e[2];
}

inline Vector3 cross(const Vector3& v1, const Vector3& v2)
{
    // // fixed to work for left handedness
    // return Vector3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
    //     // v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
    //     v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0],
    //     // v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
    //     v1.e[1] * v2.e[0] - v1.e[0] * v2.e[1]);

    // one more try
    return Vector3( 
        (v1.e[2]*v2.e[1] - v1.e[1]*v2.e[2]),
        -(v1.e[2]*v2.e[0] - v1.e[0]*v2.e[2]),
        (v1.e[1]*v2.e[0] - v1.e[0]*v2.e[1]) 
    ); 
}

inline Vector3& Vector3::operator+=(const Vector3& v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline Vector3& Vector3::operator*=(const Vector3& v)
{
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline Vector3& Vector3::operator/=(const Vector3& v)
{
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& v)
{
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline Vector3& Vector3::operator*=(const float t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline Vector3& Vector3::operator/=(const float t)
{
    float k = 1.0f / t;

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

inline Vector3 unit_vector(Vector3 v)
{
    return v / v.length();
}

typedef Vector3 rgb;
typedef Vector3 Point3;
typedef Vector3 Pixel;
typedef std::pair<int,int> Point2;
typedef std::pair<float,float> Point2f;

#endif
