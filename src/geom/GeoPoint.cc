#include <geom/GeoPoint.h>

namespace ep {
namespace geom {

GeoPoint::GeoPoint(GeoCoordinate &&coord)
    : coord_(std::move(coord))
{
}

GeoCoordinate *GeoPoint::getCoordinate()
{
    return &coord_;
}

const GeoCoordinate *GeoPoint::getCoordinate() const
{
    return &coord_;
}

#ifdef EP_OPENGL
void GeoPoint::draw() const {
  coord_.draw();
}
#endif

std::string GeoPoint::getGeometryType() const
{
    return "POINT";
}


} // namespace geom
} // namespace ep