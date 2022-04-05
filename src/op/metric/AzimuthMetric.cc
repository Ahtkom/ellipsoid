#include <op/metric/AzimuthMetric.h>
#include <algorithm/alg.h>
#include <math.h>
#include <iostream>
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
namespace op {

double
AzimuthMetric::azimuthCoordinates(const geom::GeoCoordinate *from, const geom::GeoCoordinate *to)
{
    
}

double
AzimuthMetric::azimuthPoints(const geom::GeoPoint *from, const geom::GeoPoint *to)
{
    
}


} // namespace op
} // namespace ep