#include <op/metric/LengthMetric.h>
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
namespace op {

LengthMetric::LengthMetric(const geom::GeoEarth &earth)
    : dm_(earth)
{
}

double
LengthMetric::evaluateLength(const geom::GeoGeometry *geometry)
{
    if (geometry->getGeometryType() == "LINESEGMENT") {
        return lengthOfLineSegment(static_cast<const geom::GeoLineSegment *>(geometry));
    } else if (geometry->getGeometryType() == "LINESTRING" ||
            geometry->getGeometryType() == "LINEARRING") {
        return lengthOfLineString(static_cast<const geom::GeoLineString *>(geometry));
    } else if (geometry->getGeometryType() == "MULTILINESTRING") {
        return lengthOfMultiLineString(static_cast<const geom::GeoMultiLineString *>(geometry));
    }
    return -1.0;
}

double
LengthMetric::lengthOfLineSegment(const geom::GeoLineSegment *seg)
{
    return dm_.evaluateDistance(seg->getFromPoint(), seg->getToPoint());
}

double
LengthMetric::lengthOfLineString(const geom::GeoLineString *ls)
{
    double length = 0, n = ls->getCoordinates()->getNumCoordinate();
    for (std::size_t i = 0; i != n - 1; ++i) {
        length += dm_.distanceCoordinates(ls->getCoordinateN(i), ls->getCoordinateN(i + 1));
    }
    return length;
}

double
LengthMetric::lengthOfMultiLineString(const geom::GeoMultiLineString *mls)
{
    double length = 0, n = mls->getNumLineString();
    for (std::size_t i = 0; i != n; ++i) {
        length += lengthOfLineString(mls->getLineStringN(i));
    }
    return length;
}




} // namespace op
} // namespace ep