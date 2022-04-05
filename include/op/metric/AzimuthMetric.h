#ifndef ELLIPSOID_OP_METRIC_AZIMUTHMETRIC_H_
#define ELLIPSOID_OP_METRIC_AZIMUTHMETRIC_H_

#include <geom/GeoGeometry.h>
#include <geom/GeoEarth.h>
#include <op/metric/BaseMetric.h>

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
namespace op {

class AzimuthMetric : public BaseMetric
{
public:
    AzimuthMetric(const geom::GeoEarth &earth);

    ~AzimuthMetric() override = default;

    double evaluateAzimuth(const geom::GeoGeometry *from, const geom::GeoGeometry *to);

// private:
public:
    double azimuthCoordinates(const geom::GeoCoordinate *from, const geom::GeoCoordinate *to);

    double azimuthPoints(const geom::GeoPoint *from, const geom::GeoPoint *to);

};

} // namespace op
} // namespace ep

#endif