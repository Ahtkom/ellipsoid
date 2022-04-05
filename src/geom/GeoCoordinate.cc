#include <geom/GeoCoordinate.h>

namespace ep {
namespace geom {

GeoCoordinate::GeoCoordinate(double lon, double lat)
    : lon_(lon)
    , lat_(lat)
{
}

double GeoCoordinate::getLon() const
{
    return lon_;
}

double GeoCoordinate::getLat() const
{
    return lat_;
}

std::ostream &operator<<(std::ostream &os, const GeoCoordinate &coord)
{
    os << "GeoCoordinate[" << coord.getLon() << "," << coord.getLat() << "]";
    return os;
}

} // namespace geom
} // namespace ep