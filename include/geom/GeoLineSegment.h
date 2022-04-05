#ifndef ELLIPSOID_GEOM_GEOLINESEGMENT_H_
#define ELLIPSOID_GEOM_GEOLINESEGMENT_H_

#include <geom/GeoGeometry.h>
#include <geom/GeoPoint.h>
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

    GeoPoint *getFromPoint();

    const GeoPoint *getFromPoint() const;

    GeoPoint *getToPoint();

    const GeoPoint *getToPoint() const;

protected:
    GeoLineSegment(GeoPoint::Ptr &&from, GeoPoint::Ptr &&to);

private:
    GeoPoint::Ptr from_;
    GeoPoint::Ptr to_;
};


} // namespace geom
} // namespace ep

#endif