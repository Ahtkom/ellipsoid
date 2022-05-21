#include <op/metric/AreaMetric.h>

#include <geom/GeoLinearRing.h>
#include <geom/GeoPolygon.h>
#include <geom/GeoMultiPolygon.h>

namespace ep {
namespace op {

AreaMetric::AreaMetric(const geom::GeoEarth &earth)
    : BaseMetric(earth)
{
}

double AreaMetric::evaluateArea(const geom::GeoGeometry *geometry)
{
    // TODO Implement
    return 0.0;
}

double AreaMetric::areaOfLinearRing(const geom::GeoLinearRing *lr)
{
    // TODO Implement
    return 0.0;
}

double AreaMetric::areaOfPolygon(const geom::GeoPolygon *p)
{
    // TODO Implement
    return 0.0;
}

double AreaMetric::areaOfMultiPolygon(const geom::GeoMultiPolygon *mp)
{
    // TODO Implement
    return 0.0;
}

} // namespace op
} // namespace ep