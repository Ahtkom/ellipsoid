#ifndef ELLIPSOID_GEOM_GEOGEOMETRY_H_
#define ELLIPSOID_GEOM_GEOGEOMETRY_H_

#include "ds/Area.h"
#include "ds/Length.h"
#include "geom/GeoEnvelope.h"
#include "geom/GeoReferenceSystem.h"

#include <memory>
#include <string>
#include <vector>

namespace ep {
namespace geom {
class GeoPoint;
} // namespace geom
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
class GeoGeometry
{
public:
  using Ptr = std::unique_ptr<GeoGeometry>;

  explicit GeoGeometry(GeoReferenceSystem ref);
  virtual ~GeoGeometry() = default;

  virtual std::string getGeometryType() const = 0;

  GeoReferenceSystem getGeoReference() const;
  void               setGeoReference(GeoReferenceSystem ref);

  // virtual const GeoEnvelope *getEnvelope() const;
  // virtual std::unique_ptr<GeoEnvelope> getEnvelopeNew() const;

  // virtual std::unique_ptr<GeoPoint> getCentroid() const;

  // virtual ds::Area   getArea() const;
  // virtual ds::Length getLength() const;

  // virtual ds::Length distance(const GeoGeometry *g) const;

  // virtual bool intersects(const GeoGeometry *g) const;
  // virtual bool touches(const GeoGeometry *g) const;
  // virtual bool crosses(const GeoGeometry *g) const;
  // virtual bool contains(const GeoGeometry *g) const;
  // virtual bool within(const GeoGeometry *g) const;
  // virtual bool disjoint(const GeoGeometry *g) const;
  // virtual bool overlaps(const GeoGeometry *g) const;

  virtual std::string toGeoJson() const;
  virtual std::string toWKT() const;

  virtual bool isSimple() const { return true; }

#ifdef EP_OPENGL
  virtual void draw() const = 0;
#endif

private:
  GeoReferenceSystem refsys_;

  mutable std::unique_ptr<GeoEnvelope> envelope_ = nullptr;
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_GEOGEOMETRY_H_