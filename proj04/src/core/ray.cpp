#include "ray.hpp"

std::ostream& operator<<(std::ostream& os, const Ray& r)
{
  os << "o: " << r.o << "; d: " << r.d;
  return os;
}

Point3 Ray::operator() (float t) const {
return o + d * t; 
}
