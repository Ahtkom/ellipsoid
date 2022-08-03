#ifndef ELLIPSOID_GEOM_GEOCOORDINATE_H_
#define ELLIPSOID_GEOM_GEOCOORDINATE_H_

#include <util/Macro.h>

#include <memory>

namespace ep {
namespace geom {

class GeoCoordinate {
public:
  GeoCoordinate(double lon = 0.0, double lat = 0.0);

  ~GeoCoordinate() = default;

  double getLon() const;
  double getLat() const;

  TO_STRING_METHOD_WITH_OSTREAM(GeoCoordinate)

#ifdef EP_OPENGL
  void draw() const;
#endif

private:
  double lon_;
  double lat_;
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_GEOCOORDINATE_H_