#ifndef ELLIPSOID_GEOM_GEOFACTORY_H_
#define ELLIPSOID_GEOM_GEOFACTORY_H_

#include <geom/GeoGeometry.h>
#include <memory>
#include <vector>

namespace ep {
namespace geom {
class GeoCoordinate;
class GeoCoordinateSequence;
class GeoPoint;
class GeoLineSegment;
class GeoLineString;
class GeoLinearRing;
class GeoPolygon;
class GeoMultiLineString;
class GeoMultiPolygon;
}
}

namespace ep {
namespace geom {

/**
 * @brief Factory class used to create instances of geometry objects.
 */
class GeoFactory
{
public:
    GeoFactory() = default;
    
    ~GeoFactory() = default;

    GeoCoordinate createGeoCoordinate(double lon, double lat);

    std::unique_ptr<GeoCoordinateSequence> createGeoCoordinateSequence(std::vector<GeoCoordinate> &&coords);

    std::unique_ptr<GeoPoint> createGeoPoint(GeoCoordinate &&coord);

    std::unique_ptr<GeoLineSegment> createGeoLineSegment(GeoCoordinate &&from, GeoCoordinate &&to);

    std::unique_ptr<GeoLineSegment> createGeoLineSegment(std::vector<GeoCoordinate> &&coords);

    std::unique_ptr<GeoLineSegment> createGeoLineSegment(std::unique_ptr<GeoCoordinateSequence> &&cseq);

    std::unique_ptr<GeoLineString> createGeoLineString(std::unique_ptr<GeoCoordinateSequence> &&cseq);

    std::unique_ptr<GeoLinearRing> createGeoLinearRing(std::unique_ptr<GeoCoordinateSequence> &&cseq);

    std::unique_ptr<GeoLinearRing> createGeoLinearRing(std::unique_ptr<GeoLineString> &&ls);

    std::unique_ptr<GeoPolygon> createGeoPolygon(std::unique_ptr<GeoLinearRing> &&shell);

    std::unique_ptr<GeoPolygon> createGeoPolygon(std::unique_ptr<GeoLinearRing> &&shell, 
                                                 std::vector<std::unique_ptr<GeoLinearRing>> &&holes);

    std::unique_ptr<GeoPolygon> createGeoPolygon(std::vector<std::unique_ptr<GeoLinearRing>> &&rings);

    std::unique_ptr<GeoMultiLineString> createGeoMultiLineString(std::vector<std::unique_ptr<GeoLineString>> &&lines);

    std::unique_ptr<GeoMultiPolygon> createGeoMultiPolygon(std::vector<std::unique_ptr<GeoPolygon>> &&ps);
};


} // namespace geom
} // namespace ep   

#endif