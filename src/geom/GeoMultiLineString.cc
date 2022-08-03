#include "geom/GeoMultiLineString.h"

#include "geom/GeoGeometry.h"
#include "geom/GeoReferenceSystem.h"

namespace ep {
namespace geom {

GeoMultiLineString::GeoMultiLineString(
    std::vector<GeoLineString::Ptr> &&lines, GeoReferenceSystem ref)
    : GeoGeometry(ref)
    , lines_(std::move(lines)) { }

std::string
GeoMultiLineString::getGeometryType() const {
  return "MULTILINESTRING";
}

std::size_t
GeoMultiLineString::getNumLineString() const {
  return lines_.size();
}

GeoLineString *
GeoMultiLineString::getLineString(std::size_t index) {
  return lines_[index].get();
}

const GeoLineString *
GeoMultiLineString::getLineString(std::size_t index) const {
  return lines_[index].get();
}

#ifdef EP_OPENGL
void
GeoMultiLineString::draw() const {
  for (std::size_t i = 0; i != getNumLineString(); ++i) {
    lines_[i]->draw();
  }
}
#endif

} // namespace geom
} // namespace ep
