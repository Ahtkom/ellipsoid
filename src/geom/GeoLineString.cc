#include "geom/GeoLineString.h"

#include "geom/GeoGeometry.h"

namespace ep {
namespace geom {

GeoLineString::GeoLineString(
    GeoCoordinateSequence::Ptr &&pts, GeoReferenceSystem ref)
    : GeoGeometry(ref)
    , pts_(std::move(pts)) { }

std::string
GeoLineString::getGeometryType() const {
  return "LINESTRING";
}

std::size_t
GeoLineString::getNumCoordinate() const {
  return getCoordinates()->getNumCoordinate();
}

GeoCoordinate *
GeoLineString::getCoordinate(std::size_t index) {
  return pts_->getCoordinate(index);
}

const GeoCoordinate *
GeoLineString::getCoordinate(std::size_t index) const {
  return pts_->getCoordinate(index);
}

GeoCoordinateSequence *
GeoLineString::getCoordinates() {
  return pts_.get();
}

const GeoCoordinateSequence *
GeoLineString::getCoordinates() const {
  return pts_.get();
}

bool
GeoLineString::isRing() const {
  return isClosed() && isSimple();
}

// TODO
bool
GeoLineString::isClosed() const {
  return true;
}

#ifdef EP_OPENGL
void
GeoLineString::draw() const {
  pts_->draw();
}
#endif

} // namespace geom
} // namespace ep