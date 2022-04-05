#include <geom/GeoPoint.h>

namespace ep {
namespace geom {

GeoPoint::GeoPoint(GeoCoordinate::Ptr &&coord)
    : coord_(std::move(coord))
{
}

GeoCoordinate *GeoPoint::getCoordinate()
{
    return coord_.get();
}

const GeoCoordinate *GeoPoint::getCoordinate() const
{
    return coord_.get();
}



std::string GeoPoint::getGeometryType() const
{
    return "POINT";
}


} // namespace geom
} // namespace ep