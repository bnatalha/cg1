#ifndef HEADER_HPP
#define HEADER_HPP

#define DEFAULT_COLOR "0 0 0"
#define DEFAULT_MAPPING "screen"

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef TO_RADIANS
#define TO_RADIANS(degrees)         \
  degrees * M_PI / 180.f;

#endif

#endif
