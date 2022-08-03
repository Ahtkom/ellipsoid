#include "geom/GeoLineSegment.h"

#include "geom/GeoCoordinate.h"
#include "geom/GeoGeometry.h"
#include "geom/GeoReferenceSystem.h"

namespace ep {
namespace geom {

GeoLineSegment::GeoLineSegment(
    GeoCoordinate &&from, GeoCoordinate &&to, GeoReferenceSystem ref)
    : GeoGeometry(ref)
    , from_(from)
    , to_(to) { }

std::string
GeoLineSegment::getGeometryType() const {
  return "LINESEGMENT";
}

GeoCoordinate *
GeoLineSegment::getFromCoordinate() {
  return &from_;
}

const GeoCoordinate *
GeoLineSegment::getFromCoordinate() const {
  return &from_;
}

GeoCoordinate *
GeoLineSegment::getToCoordinate() {
  return &to_;
}

const GeoCoordinate *
GeoLineSegment::getToCoordinate() const {
  return &to_;
}

#ifdef EP_OPENGL
void
GeoLineSegment::draw() const {
  from_->draw();
  to_->draw();
}
#endif

} // namespace geom
} // namespace ep