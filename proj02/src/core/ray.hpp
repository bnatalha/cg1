#ifndef RAY_HPP
#define RAY_HPP

#include "header.hpp"
#include "vector3.hpp"
#include "tinyxml2.hpp"

using std::string;
class Ray {

  public:
    Ray (const Point3& o, const Vector3& d) : o{o}, d{d} 
    {
    }

  private:
    Point3 o; //!< origin
    Vector3 d;

    Point3 operator() (float t) const {return o + d * t;}

};

#endif
