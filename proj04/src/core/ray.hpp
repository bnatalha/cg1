#ifndef RAY_HPP
#define RAY_HPP

#include "vector3.hpp"

#include <climits>
#include <limits>

using std::string;
class Ray {

public:
  Ray(const Point3& o, const Vector3& d) : o{ o }, d{ d } {}

  Point3 o; //!< origin
  Vector3 d;
  float mutable t_min = 0.f;
  float mutable t_max = std::numeric_limits<float>::max();;

  Point3 operator() (float t) const;
  // Point3 operator() (float t) const { return o + d * t; }
  
};

#endif
