#include <geom/GeoLineString.h>

namespace ep {
namespace geom {

GeoLineString::GeoLineString(GeoCoordinateSequence::Ptr &&pts)
    : pts_(std::move(pts)) {}

std::string GeoLineString::getGeometryType() const { return "LINESTRING"; }

GeoCoordinate *GeoLineString::getCoordinateN(std::size_t index) {
  return pts_->getCoordinateN(index);
}

const GeoCoordinate *GeoLineString::getCoordinateN(std::size_t index) const {
  return pts_->getCoordinateN(index);
}

GeoCoordinateSequence *GeoLineString::getCoordinates() { return pts_.get(); }

const GeoCoordinateSequence *GeoLineString::getCoordinates() const {
  return pts_.get();
}

bool GeoLineString::isRing() const { return isClosed() && isSimple(); }

// TODO
bool GeoLineString::isClosed() const { return true; }

#ifdef EP_OPENGL
void GeoLineString::draw() const {
  pts_->draw();
}
#endif

} // namespace geom
} // namespace ep