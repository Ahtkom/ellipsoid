#include <geom/GeoLinearRing.h>

namespace ep {
namespace geom {

GeoLinearRing::GeoLinearRing(GeoCoordinateSequence::Ptr &&pts)
    : GeoLineString(std::move(pts))
{
}

std::string GeoLinearRing::getGeometryType() const
{
    return "LINEARRING";
}

// TODO
bool GeoLinearRing::isClosed() const
{
    return true;
}

} // namespace geom
} // namespace ep