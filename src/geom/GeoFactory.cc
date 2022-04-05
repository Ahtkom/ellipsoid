#include <geom/GeoFactory.h>

#include <geom/GeoCoordinate.h>
#include <geom/GeoCoordinateSequence.h>
#include <geom/GeoPoint.h>
#include <geom/GeoLineSegment.h>
#include <geom/GeoLineString.h>
#include <geom/GeoLinearRing.h>
#include <geom/GeoPolygon.h>
#include <geom/GeoMultiLineString.h>
#include <geom/GeoMultiPolygon.h>

namespace ep {
namespace geom {

GeoCoordinate
GeoFactory::createGeoCoordinate(double lon, double lat)
{
    return {lon, lat};
}

GeoCoordinateSequence::Ptr
GeoFactory::createGeoCoordinateSequence(std::vector<GeoCoordinate> &&coords)
{
    std::vector<GeoCoordinate::Ptr> coordPtrs;
    for (std::size_t i = 0; i != coords.size(); ++i) {
        coordPtrs.push_back(std::make_unique<GeoCoordinate>(std::move(coords[i])));
    }
    return std::unique_ptr<GeoCoordinateSequence>(
        new GeoCoordinateSequence(std::move(coordPtrs)));
}

GeoPoint::Ptr
GeoFactory::createGeoPoint(GeoCoordinate &&coord)
{
    return std::unique_ptr<GeoPoint>(
        new GeoPoint(std::make_unique<GeoCoordinate>(coord)));
}

GeoLineSegment::Ptr
GeoFactory::createGeoLineSegment(GeoCoordinate &&from, GeoCoordinate &&to)
{
    return std::unique_ptr<GeoLineSegment>(
        new GeoLineSegment(createGeoPoint(std::move(from)),
                           createGeoPoint(std::move(to))));
}

GeoLineSegment::Ptr
GeoFactory::createGeoLineSegment(std::vector<GeoCoordinate> &&coords)
{
    return createGeoLineSegment(std::move(coords.front()), std::move(coords.back()));
}

GeoLineSegment::Ptr
GeoFactory::createGeoLineSegment(GeoCoordinateSequence::Ptr &&cseq)
{
    return std::unique_ptr<GeoLineSegment>(
        new GeoLineSegment(createGeoPoint(std::move(*cseq->coords_[0])),
                           createGeoPoint(std::move(*cseq->coords_[1]))));
}


GeoLineString::Ptr
GeoFactory::createGeoLineString(GeoCoordinateSequence::Ptr &&cseq)
{
    return std::unique_ptr<GeoLineString>(new GeoLineString(std::move(cseq)));
}

GeoLinearRing::Ptr
GeoFactory::createGeoLinearRing(GeoCoordinateSequence::Ptr &&cseq)
{
    // TODO: check whether it is closed
    return std::unique_ptr<GeoLinearRing>(new GeoLinearRing(std::move(cseq)));
}

GeoLinearRing::Ptr
GeoFactory::createGeoLinearRing(GeoLineString::Ptr &&ls)
{
    // TODO
    // return std::unique_ptr<GeoLinearRing>(new GeoLinearRing(ls));
}

GeoPolygon::Ptr
GeoFactory::createGeoPolygon(GeoLinearRing::Ptr &&shell)
{
    return std::unique_ptr<GeoPolygon>(new GeoPolygon(std::move(shell)));
}

GeoPolygon::Ptr
GeoFactory::createGeoPolygon(GeoLinearRing::Ptr &&shell,
                             std::vector<GeoLinearRing::Ptr> &&holes)
{
    return std::unique_ptr<GeoPolygon>(
        new GeoPolygon(std::move(shell), std::move(holes)));
}

GeoPolygon::Ptr
GeoFactory::createGeoPolygon(std::vector<GeoLinearRing::Ptr> &&rings)
{
    GeoLinearRing::Ptr shell = std::move(rings[0]);
    rings.erase(rings.begin());
    return createGeoPolygon(std::move(shell), std::move(rings));
}

GeoMultiLineString::Ptr
GeoFactory::createGeoMultiLineString(std::vector<GeoLineString::Ptr> &&lines)
{
    return std::unique_ptr<GeoMultiLineString>(
        new GeoMultiLineString(std::move(lines)));
}

GeoMultiPolygon::Ptr
GeoFactory::createGeoMultiPolygon(std::vector<GeoPolygon::Ptr> &&ps)
{
    return std::unique_ptr<GeoMultiPolygon>(new GeoMultiPolygon(std::move(ps)));
}

} // namespace geom
} // namespace ep   