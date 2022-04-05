#include <geom/GeoMultiLineString.h>

namespace ep {
namespace geom {

GeoMultiLineString::GeoMultiLineString(std::vector<GeoLineString::Ptr> &&lines)
    : lines_(std::move(lines))
{
}

std::string GeoMultiLineString::getGeometryType() const
{
    return "MULTILINESTRING";
}

std::size_t GeoMultiLineString::getNumLineString() const
{
    return lines_.size();
}

GeoLineString *GeoMultiLineString::getLineStringN(std::size_t index)
{
    return lines_[index].get();
}

const GeoLineString *GeoMultiLineString::getLineStringN(std::size_t index) const
{
    return lines_[index].get();
}


} // namespace geom
} // namespace ep
