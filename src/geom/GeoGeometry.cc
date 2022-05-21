#include <geom/GeoGeometry.h>

#include <geom/GeoEarth.h>
#include <io/GeoJsonWriter.h>
#include <io/WKTWriter.h>
#include <op/metric/DistanceMetric.h>

namespace ep {
namespace geom {

static op::DistanceMetric dm(GeoEarth::GeoEarth_WGS84);
static io::WKTWriter wkt_writer;
static io::GeoJsonWriter json_writer;

std::string GeoGeometry::toGeoJson() const { return json_writer.write(this); }

std::string GeoGeometry::toWKT() const { return wkt_writer.write(this); }

double GeoGeometry::distance(const GeoGeometry *g, GeoEarth earth) const {
  dm.setGeoEarth(earth);
  return dm.distance(this, g);
}

} // namespace geom
} // namespace ep