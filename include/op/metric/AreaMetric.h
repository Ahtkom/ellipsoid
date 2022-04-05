#ifndef ELLIPSOID_OP_METRIC_AREAMETRIC_H_
#define ELLIPSOID_OP_METRIC_AREAMETRIC_H_

#include <geom/GeoGeometry.h>
#include <geom/GeoEarth.h>

namespace ep {
namespace geom {
class GeoLinearRing;
class GeoPolygon;
class GeoMultiPolygon;
}
}

namespace ep {
namespace op {

class AreaMetric
{
public:
    AreaMetric(const geom::GeoEarth &earth);

    ~AreaMetric() = default;

    geom::GeoEarth getGeoEarth() const;

    void setGeoEarth(const geom::GeoEarth &earth);

    double evaluateArea(const geom::GeoGeometry *geometry);

private:
    double areaOfLinearRing(const geom::GeoLinearRing *lr);

    double areaOfPolygon(const geom::GeoPolygon *p);

    double areaOfMultiPolygon(const geom::GeoMultiPolygon *mp);

private:
    geom::GeoEarth earth_;
};

} // namespace op
} // namespace ep


#endif