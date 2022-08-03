#include "geom/GeoReferenceSystem.h"

#include "geom/Ellipsoid.h"

namespace ep {
namespace geom {

const GeoReferenceSystem GeoReferenceSystem::undefined{0};
const GeoReferenceSystem GeoReferenceSystem::WGS84{4326};
const GeoReferenceSystem GeoReferenceSystem::CGCS2000{4490};

const std::map<unsigned, Ellipsoid> GeoReferenceSystem::ellipsoids = {
    {   0, Ellipsoid::Undefined},
    {4326,    Ellipsoid::WGS_84},
    {4490, Ellipsoid::CGCS_2000},
};

Ellipsoid
GeoReferenceSystem::getEllipsoid() const {
  return GeoReferenceSystem::ellipsoids.at(getSRID());
}

GeoReferenceSystem::GeoReferenceSystem(unsigned srid) {
  if (GeoReferenceSystem::ellipsoids.count(srid) != -1) {
    srid_ = srid;
  }
  // TODO: throw
}

} // namespace geom
} // namespace ep