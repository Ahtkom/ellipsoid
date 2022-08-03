#include "geom/GeoPoint.h"

#include "geom/GeoCoordinate.h"
#include "geom/GeoGeometry.h"
#include "geom/GeoReferenceSystem.h"

#include <utility>


namespace ep {
namespace geom {

GeoPoint::GeoPoint(GeoCoordinate &&coord, GeoReferenceSystem ref)
    : GeoGeometry(ref)
    , coord_(std::move(coord)) { }

GeoCoordinate *
GeoPoint::getCoordinate() {
  return &coord_;
}

const GeoCoordinate *
GeoPoint::getCoordinate() const {
  return &coord_;
}

#ifdef EP_OPENGL
void
GeoPoint::draw() const {
  coord_.draw();
}
#endif

std::string
GeoPoint::getGeometryType() const {
  return "POINT";
}

} // namespace geom
} // namespace ep