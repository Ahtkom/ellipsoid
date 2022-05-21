#ifndef ELLIPSOID_GEOM_GEOPOINT_H_
#define ELLIPSOID_GEOM_GEOPOINT_H_

#include <geom/GeoCoordinate.h>
#include <geom/GeoGeometry.h>

#include <memory>
#include <string>

namespace ep {
namespace geom {

class GeoPoint : public GeoGeometry {
  friend class GeoFactory;

public:
  using Ptr = std::unique_ptr<GeoPoint>;

  ~GeoPoint() override = default;

  GeoCoordinate *getCoordinate();

  const GeoCoordinate *getCoordinate() const;

  std::string getGeometryType() const override;

#ifdef EP_OPENGL
  void draw() const override;
#endif

protected:
  GeoPoint(GeoCoordinate &&coord);

private:
  GeoCoordinate coord_;
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_GEOPOINT_H_