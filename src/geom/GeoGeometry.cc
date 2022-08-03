#include "geom/GeoGeometry.h"

#include "geom/GeoEnvelope.h"
#include "geom/GeoReferenceSystem.h"

#include <geom/GeoEarth.h>
#include <io/GeoJsonWriter.h>
#include <io/WKTWriter.h>
#include <memory>
// #include <op/metric/DistanceMetric.h>

namespace ep {
namespace geom {

// static op::DistanceMetric dm(GeoEarth::GeoEarth_WGS84);
static io::WKTWriter     wktWriter;
static io::GeoJsonWriter jsonWriter;

GeoGeometry::GeoGeometry(GeoReferenceSystem ref)
    : refsys_(ref) { }

GeoReferenceSystem
GeoGeometry::getGeoReference() const {
  return refsys_;
}

void
GeoGeometry::setGeoReference(GeoReferenceSystem ref) {
  refsys_ = ref;
}

std::unique_ptr<GeoEnvelope>
GeoGeometry::getEnvelopeNew() const {
  return std::unique_ptr<GeoEnvelope>(new GeoEnvelope(*getEnvelope()));
}

std::string
GeoGeometry::toGeoJson() const {
  return jsonWriter.write(this);
}

std::string
GeoGeometry::toWKT() const {
  return wktWriter.write(this);
}

// double GeoGeometry::distance(const GeoGeometry *g, GeoEarth earth) const {
//   dm.setGeoEarth(earth);
//   return dm.distance(this, g);
// }

} // namespace geom
} // namespace ep