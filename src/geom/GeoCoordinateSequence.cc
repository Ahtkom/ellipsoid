#include <geom/GeoCoordinateSequence.h>

namespace ep {
namespace geom {

GeoCoordinateSequence::GeoCoordinateSequence(std::vector<GeoCoordinate::Ptr> &&coords)
    : coords_(std::move(coords))
{
}

std::size_t GeoCoordinateSequence::getNumCoordinate() const
{
    return coords_.size();
}

GeoCoordinate *GeoCoordinateSequence::getCoordinateN(std::size_t index)
{
    return coords_[index].get();
}

const GeoCoordinate *GeoCoordinateSequence::getCoordinateN(std::size_t index) const
{
    return coords_[index].get();
}

std::ostream &operator<<(std::ostream &os, const GeoCoordinateSequence &coords)
{
    os << "CoordinateSequence[";
    auto n = coords.getNumCoordinate();
    if (n == 0) {
        return os << "]";
    }
    for (std::size_t i = 0; i != n - 1; ++i) {
        os << *coords.getCoordinateN(i) << ", ";
    }
    os << *coords.getCoordinateN(n - 1) << "]";
    return os;
}

} // namespace geom
} // namespace ep