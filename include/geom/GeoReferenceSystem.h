#ifndef ELLIPSOID_GEOM_GEOREFERENCESYSTEM_H_
#define ELLIPSOID_GEOM_GEOREFERENCESYSTEM_H_

#include "geom/Ellipsoid.h"

#include <map>
#include <vector>

namespace ep {
namespace geom {

class GeoReferenceSystem
{
public:
  static const GeoReferenceSystem undefined;
  static const GeoReferenceSystem WGS84;
  static const GeoReferenceSystem CGCS2000;
  static const std::map<unsigned, Ellipsoid> ellipsoids;

  explicit GeoReferenceSystem(unsigned srid);

  Ellipsoid getEllipsoid() const;

  unsigned getSRID() const { return srid_; }
  void setSRID(unsigned srid) { srid_ = srid; }

private:
  unsigned srid_;
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_GEOREFERENCESYSTEM_H_