#ifndef ELLIPSOID_OP_METRIC_AREAMETRIC_H_
#define ELLIPSOID_OP_METRIC_AREAMETRIC_H_

#include <geom/GeoGeometry.h>
#include <geom/GeoEarth.h>
#include <op/metric/BaseMetric.h>

namespace ep {
namespace geom {
class GeoLinearRing;
class GeoPolygon;
class GeoMultiPolygon;
}
}

namespace ep {
namespace op {

class AreaMetric : public BaseMetric
{
public:
    AreaMetric(const geom::GeoEarth &earth);

    ~AreaMetric() = default;

    double evaluateArea(const geom::GeoGeometry *geometry);

private:
    double areaOfLinearRing(const geom::GeoLinearRing *lr);

    double areaOfPolygon(const geom::GeoPolygon *p);

    double areaOfMultiPolygon(const geom::GeoMultiPolygon *mp);
};

} // namespace op
} // namespace ep


#endif