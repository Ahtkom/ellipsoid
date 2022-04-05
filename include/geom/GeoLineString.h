#ifndef ELLIPSOID_GEOM_GEOLINESTRING_H_
#define ELLIPSOID_GEOM_GEOLINESTRING_H_

#include <geom/GeoGeometry.h>
#include <geom/GeoCoordinateSequence.h>
#include <memory>

namespace ep {
namespace geom {

class GeoLineString : public GeoGeometry
{
    friend class GeoFactory;

public:
    using Ptr = std::unique_ptr<GeoLineString>;

    /** \brief
     * The minimum number of vertices allowed in a valid non-empty ring.
     * Empty rings with 0 vertices are also valid.
     */
    static const unsigned int MINIMUM_VALID_SIZE = 3;

    ~GeoLineString() override = default;

    std::string getGeometryType() const override;

    GeoCoordinate *getCoordinateN(std::size_t index);

    const GeoCoordinate *getCoordinateN(std::size_t index) const;

    GeoCoordinateSequence *getCoordinates();

    const GeoCoordinateSequence *getCoordinates() const;

    virtual bool isClosed() const;

    virtual bool isRing() const;

protected:
    GeoLineString(GeoCoordinateSequence::Ptr &&pts);

protected:
    GeoCoordinateSequence::Ptr pts_;
};

} // namespace geom
} // namespace ep

#endif