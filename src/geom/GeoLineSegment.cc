#include <geom/GeoLineSegment.h>

namespace ep {
namespace geom {

GeoLineSegment::GeoLineSegment(GeoPoint::Ptr &&from, GeoPoint::Ptr &&to)
    : from_(std::move(from)), to_(std::move(to)) {}

std::string GeoLineSegment::getGeometryType() const { return "LINESEGMENT"; }

GeoPoint *GeoLineSegment::getFromPoint() { return from_.get(); }

const GeoPoint *GeoLineSegment::getFromPoint() const { return from_.get(); }

GeoPoint *GeoLineSegment::getToPoint() { return to_.get(); }

const GeoPoint *GeoLineSegment::getToPoint() const { return to_.get(); }

#ifdef EP_OPENGL
void GeoLineSegment::draw() const {
  from_->draw();
  to_->draw();
}
#endif

} // namespace geom
} // namespace ep