#ifndef ELLIPSOID_GEOM_GEOLINESEGMENT_H_
#define ELLIPSOID_GEOM_GEOLINESEGMENT_H_

#include "geom/GeoCoordinate.h"
#include "geom/GeoGeometry.h"
#include "geom/GeoPoint.h"
#include "geom/GeoReferenceSystem.h"

#include <memory>

namespace ep {
namespace geom {

class GeoLineSegment : public GeoGeometry
{
  friend class GeoFactory;

public:
  using Ptr = std::unique_ptr<GeoLineSegment>;

  ~GeoLineSegment() override = default;

  std::string getGeometryType() const override;

  GeoCoordinate       *getFromCoordinate();
  const GeoCoordinate *getFromCoordinate() const;

  GeoCoordinate       *getToCoordinate();
  const GeoCoordinate *getToCoordinate() const;

  std::unique_ptr<GeoPoint> getFromPoint() const;
  std::unique_ptr<GeoPoint> getToPoint() const;

#ifdef EP_OPENGL
  void draw() const override;
#endif

protected:
  GeoLineSegment(
      GeoCoordinate &&from, GeoCoordinate &&to, GeoReferenceSystem ref);

private:
  GeoCoordinate from_; // From point

  GeoCoordinate to_; // To Point
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_GEOLINESEGMENT_H_