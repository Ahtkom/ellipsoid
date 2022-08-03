#include "geom/GeoPolygon.h"

#include "geom/GeoGeometry.h"
#include "geom/GeoReferenceSystem.h"

namespace ep {
namespace geom {

GeoPolygon::GeoPolygon(GeoLinearRing::Ptr &&shell, GeoReferenceSystem ref)
    : GeoGeometry(ref)
    , shell_(std::move(shell)) { }

GeoPolygon::GeoPolygon(GeoLinearRing::Ptr &&shell,
    std::vector<GeoLinearRing::Ptr> &&holes, GeoReferenceSystem ref)
    : GeoGeometry(ref)
    , shell_(std::move(shell))
    , holes_(std::move(holes)) { }

std::string
GeoPolygon::getGeometryType() const {
  return "POLYGON";
}

std::size_t
GeoPolygon::getNumInteriorRing() const {
  return holes_.size();
}

GeoLinearRing *
GeoPolygon::getExteriorRing() {
  return shell_.get();
}

const GeoLinearRing *
GeoPolygon::getExteriorRing() const {
  return shell_.get();
}

GeoLinearRing *
GeoPolygon::getInteriorRing(std::size_t index) {
  return holes_[index].get();
}

const GeoLinearRing *
GeoPolygon::getInteriorRing(std::size_t index) const {
  return holes_[index].get();
}

#ifdef EP_OPENGL
void
GeoPolygon::draw() const {
  shell_->draw();
}
#endif

} // namespace geom
} // namespace ep
