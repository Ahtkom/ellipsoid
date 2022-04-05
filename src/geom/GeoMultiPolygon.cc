#include <geom/GeoMultiPolygon.h>

namespace ep {
namespace geom {

GeoMultiPolygon::GeoMultiPolygon(std::vector<GeoPolygon::Ptr> &&ps)
    : ps_(std::move(ps))
{
}

std::string GeoMultiPolygon::getGeometryType() const
{
    return "MULTIPOLYGON";
}

std::size_t GeoMultiPolygon::getNumPolygon() const
{
    return ps_.size();
}

GeoPolygon *GeoMultiPolygon::getPolygonN(std::size_t index)
{
    return ps_[index].get();
}

const GeoPolygon *GeoMultiPolygon::getPolygonN(std::size_t index) const
{
    return ps_[index].get();
}


} // namespace geom
} // namespace ep