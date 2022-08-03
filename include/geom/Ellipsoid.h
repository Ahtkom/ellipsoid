#ifndef ELLIPSOID_GEOM_ELLIPSOID_H_
#define ELLIPSOID_GEOM_ELLIPSOID_H_

namespace ep {
namespace geom {

class Ellipsoid
{
public:
  static const Ellipsoid Undefined;
  static const Ellipsoid CGCS_2000;
  static const Ellipsoid Bessel_1841;
  static const Ellipsoid Clarke_1866;
  static const Ellipsoid GRS_1980;
  static const Ellipsoid Krassowsky_1940;
  static const Ellipsoid WGS_84;

  const double a;
  const double alpha;
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_ELLIPSOID_H_