#include "geom/GeoLinearRing.h"

#include "geom/GeoReferenceSystem.h"

namespace ep {
namespace geom {

GeoLinearRing::GeoLinearRing(
    GeoCoordinateSequence::Ptr &&pts, GeoReferenceSystem ref)
    : GeoLineString(std::move(pts), ref) { }

std::string
GeoLinearRing::getGeometryType() const {
  return "LINEARRING";
}

// TODO
bool
GeoLinearRing::isClosed() const {
  return true;
}

} // namespace geom
} // namespace ep