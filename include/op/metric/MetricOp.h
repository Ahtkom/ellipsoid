#ifndef ELLIPSOID_OP_METRIC_METRIC_H_
#define ELLIPSOID_OP_METRIC_METRIC_H_

#include <geom/GeoGeometry.h>
#include <geom/GeoEarth.h>
#include <op/metric/AreaMetric.h>
#include <op/metric/DistanceMetric.h>
#include <op/metric/LengthMetric.h>

namespace ep {
namespace op {

/**
 * @brief MetricOp provides calcuation of area, length and distance.
 * 
 */
class MetricOp
{
public:
    MetricOp(const geom::GeoEarth &earth = geom::GeoEarth::GeoEarth_WGS84)
        : earth_(earth)
    {}

    ~MetricOp() = default;

    geom::GeoEarth getGeoEarth() const { return earth_; }

    void setGeoEarth(const geom::GeoEarth &earth) { earth_ = earth; }

    /**
     * @brief Evaluate the area of geometry on the surface of ellipsoid, support
     *        `LinearRing`, `Polygon` and `MultiPolygon`.
     * 
     * @param geometry Pointer to geometry object.
     * @return The quantity of area, 0.0 if geometry type is not supported.
     */
    double area(const geom::GeoGeometry *geometry) {
        AreaMetric areaOp(getGeoEarth());
        return areaOp.evaluateArea(geometry);
    }
    
    /**
     * @brief Evaluate the length of geometry on the surface of ellipsoid,
     *        support `GeoLineSegment`, `GeoLineString`, `GeoLinearRing`,
     *        `GeoPolygon`, `GeoMultiLineString` and `GeoMultiPolygon`.
     * 
     * @param geometry Pointer to geometry object.
     * @return The quantity of length, 0.0 if geometry type is not supported.
     */
    double length(const geom::GeoGeometry *geometry) {
        LengthMetric lengthOp(getGeoEarth());
        return lengthOp.evaluateLength(geometry);
    }

    /**
     * @brief Evaluate the distance between two geomtries along the geodesic.
     * 
     * @param g1 Pointer to geometry object.
     * @param g2 Pointer to geometry object.
     * @return The quantity of distance, 0.0 if they intersect.
     */
    double distance(const geom::GeoGeometry *g1, const geom::GeoGeometry *g2) {
        DistanceMetric distanceOp(getGeoEarth());
        return distanceOp.evaluateDistance(g1, g2);
    }

private:
    geom::GeoEarth earth_;
};

} // namespace op
} // namespace ep

#endif