#ifndef ELLIPSOID_GEOM_GEOGEOMETRY_H_
#define ELLIPSOID_GEOM_GEOGEOMETRY_H_

#include <geom/GeoEarth.h>

#include <memory>
#include <string>
#include <vector>

namespace ep {
namespace io {
class GeoJsonWriter;
class WKTWriter;
} // namespace io
namespace op {
class DistanceMetric;
} // namespace op
} // namespace ep

namespace ep {
namespace geom {

/**
 * @brief Abstract base class for geometries.
 */
class GeoGeometry {
public:
  using Ptr = std::unique_ptr<GeoGeometry>;

  using ConstVect = std::vector<const GeoGeometry *>;

  virtual ~GeoGeometry() = default;

  // Output geometry object in GeoJson string format.
  std::string toGeoJson() const;

  // Output geometry object in WKT format.
  std::string toWKT() const;

  virtual std::string getGeometryType() const = 0;

  virtual bool isSimple() const { return true; }

  double distance(const GeoGeometry *g,
                  GeoEarth earth = GeoEarth::GeoEarth_WGS84) const;

#ifdef EP_OPENGL
  virtual void draw() const = 0;
#endif
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_GEOGEOMETRY_H_