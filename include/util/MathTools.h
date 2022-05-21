#ifndef ELLIPSOID_UTIL_MATHTOOLS_H_
#define ELLIPSOID_UTIL_MATHTOOLS_H_

#include <cmath>

static constexpr double PI = 3.1415926535897;

static constexpr double EPSILON = 0.00000000001;

namespace ep {

double toDegree(double rad);

double toRadius(double deg);

} // namespace ep

#endif // ELLIPSOID_UTIL_MATHTOOLS_H_