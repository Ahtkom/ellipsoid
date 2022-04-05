#ifndef ELLIPSOID_GEOM_GEOCOORDINATESEQUENCE_H_
#define ELLIPSOID_GEOM_GEOCOORDINATESEQUENCE_H_

#include <geom/GeoCoordinate.h>
#include <vector>
#include <memory>

namespace ep {
namespace geom {

class GeoCoordinateSequence
{
    friend class GeoFactory;

public:
    using Ptr = std::unique_ptr<GeoCoordinateSequence>;

    ~GeoCoordinateSequence() = default;

    std::size_t getNumCoordinate() const;

    TO_STRING_METHOD_WITH_OSTREAM(GeoCoordinateSequence)

    GeoCoordinate *getCoordinateN(std::size_t index);

    const GeoCoordinate *getCoordinateN(std::size_t index) const;

protected:
    GeoCoordinateSequence(std::vector<GeoCoordinate::Ptr> &&coords);

private:
    std::vector<GeoCoordinate::Ptr> coords_;
};

} // namespace geom
} // namespace ep   

#endif