#ifndef ELLIPSOID_GEOM_GEOLINESEGMENT_H_
#define ELLIPSOID_GEOM_GEOLINESEGMENT_H_

#include <geom/GeoCoordinate.h>
#include <geom/GeoGeometry.h>
#include <geom/GeoPoint.h>

#include <memory>

namespace ep {
namespace geom {

class GeoLineSegment : public GeoGeometry {
  friend class GeoFactory;

public:
  using Ptr = std::unique_ptr<GeoLineSegment>;

  ~GeoLineSegment() override = default;

  std::string getGeometryType() const override;

  GeoPoint *getFromPoint();

  const GeoPoint *getFromPoint() const;

  GeoPoint *getToPoint();

  const GeoPoint *getToPoint() const;

#ifdef EP_OPENGL
  void draw() const override;
#endif

protected:
  GeoLineSegment(GeoPoint::Ptr &&from, GeoPoint::Ptr &&to);

private:
  GeoPoint::Ptr from_; // From point

  GeoPoint::Ptr to_; // To Point

  // GeoCoordinate from_;
  // GeoCoordinate to_;
  // double from_ang_;
  // double to_ang_;
  // double length_;
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_GEOLINESEGMENT_H_