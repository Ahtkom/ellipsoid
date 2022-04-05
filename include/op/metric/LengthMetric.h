#ifndef ELLIPSOID_OP_METRIC_LENGTHMETRIC_H_
#define ELLIPSOID_OP_METRIC_LENGTHMETRIC_H_

#include <geom/GeoGeometry.h>
#include <geom/GeoEarth.h>
#include <op/metric/DistanceMetric.h>

namespace ep {
namespace geom {
class GeoLineSegment;
class GeoLineString;
class GeoLinearRing;
// class GeoPolygon;
class GeoMultiLineString;
// class GeoMultiPolygon;
}
}

namespace ep {
namespace op {

class LengthMetric
{
public:
    LengthMetric(const geom::GeoEarth &earth);

    ~LengthMetric() = default;

    double evaluateLength(const geom::GeoGeometry *geometry);

private:
    double lengthOfLineSegment(const geom::GeoLineSegment *seg);

    double lengthOfLineString(const geom::GeoLineString *ls);

    // double lengthOfPolygon(const geom::GeoPolygon *p);
    
    double lengthOfMultiLineString(const geom::GeoMultiLineString *mls);
    
    // double lengthOfMultiPolygon(const geom::GeoMultiPolygon *mp);

private:
    DistanceMetric dm_;
};

} // namespace op
} // namespace ep


#endif