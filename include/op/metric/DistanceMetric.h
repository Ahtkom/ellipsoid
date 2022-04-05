#ifndef ELLIPSOID_OP_METRIC_DISTANCEMETRIC_H_
#define ELLIPSOID_OP_METRIC_DISTANCEMETRIC_H_

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

class DistanceMetric : public BaseMetric
{
public:
    DistanceMetric(const geom::GeoEarth &earth);

    ~DistanceMetric() override = default;

    double evaluateDistance(const geom::GeoGeometry *g1, const geom::GeoGeometry *g2);

    double distanceCoordinates
     (const geom::GeoCoordinate *coord1, const geom::GeoCoordinate *coord2);

protected:
    double distancePoints
     (const geom::GeoPoint *pt1, const geom::GeoPoint *pt2);

    double distancePointToLineString
     (const geom::GeoPoint *pt, const geom::GeoLineString *ls);

    double distancePointToPolygon
     (const geom::GeoPoint *pt, const geom::GeoPolygon *p);

    double distancePointToMultiLineString
     (const geom::GeoPoint *pt, const geom::GeoMultiLineString *mls);
    
    double distancePointToMultiPolygon
     (const geom::GeoPoint *pt, const geom::GeoMultiPolygon *mp);

    double distanceLineStrings
     (const geom::GeoLineString *ls1, const geom::GeoLineString *ls2);

    double distanceLineStringToPolygon
     (const geom::GeoLineString *ls, const geom::GeoPolygon *p);

    double distanceLineStringToMultiLineString
     (const geom::GeoLineString *ls, const geom::GeoMultiLineString *mls);

    double distanceLineStringToMultiPolygon
     (const geom::GeoLineString *ls, const geom::GeoMultiPolygon *mp);

    double distancePolygons
     (const geom::GeoPolygon *p1, const geom::GeoPolygon *p2);
    
    double distancePolygonToMultiLineStrin
     (const geom::GeoPolygon *p, const geom::GeoMultiLineString *mls);

    double distancePolygonToMultiPolygon
     (const geom::GeoPolygon *p, const geom::GeoMultiPolygon *mp);
    
    double distanceMultiLineStrings
     (const geom::GeoMultiLineString *mls1, const geom::GeoMultiLineString *mls2);
    
    double distanceMultiLineStringToMultiPolygon
     (const geom::GeoMultiLineString *mls, const geom::GeoMultiPolygon *mp);

    double distanceMultiPolygons
     (const geom::GeoMultiPolygon *mp1, const geom::GeoMultiPolygon *mp2);



    double distanceCoordinateToTwoCoordinates(
        const geom::GeoCoordinate *coord,
        const geom::GeoCoordinate *coord1,
        const geom::GeoCoordinate *coord2);

    double distanceCoordinateToCoordinateSequence
     (const geom::GeoCoordinate *coord, const geom::GeoCoordinateSequence *cseq);

    double distanceCoordinateSequences
     (const geom::GeoCoordinateSequence *cseq1, const geom::GeoCoordinateSequence *cseq2);

// protected:
public:
    /**
     * @brief 大地线正算，亦即大地第一主题
     * 
     * @param coord1 
     * @param a1 
     * @param a2 
     * @return 
     */
    geom::GeoCoordinate FirstTheme
     (const geom::GeoCoordinate *coord1, double dist, double a1, double &a2);

    /**
     * @brief 大地线长度计算, 亦即大地第二主题
     * 
     * @param coord1 
     * @param coord2 
     * @param a1 
     * @param a2 
     * @return 
     */
    double SecondTheme
     (const geom::GeoCoordinate *coord1, const geom::GeoCoordinate *coord2, double &a1, double &a2);

// private:
public:
    geom::GeoCoordinate Bessel_FirstTheme
     (const geom::GeoCoordinate *coord1, double dist, double a1, double &a2);

    geom::GeoCoordinate Gauss_FirstTheme
     (const geom::GeoCoordinate *coord1, double dist, double a1, double &a2);

    double Bessel_SecondTheme
     (const geom::GeoCoordinate *coord1, const geom::GeoCoordinate *coord2, double &a1, double &a2);

    double Gauss_SecondTheme
     (const geom::GeoCoordinate *coord1, const geom::GeoCoordinate *coord2, double &a1, double &a2);
};

} // namespace op
} // namespace ep

#endif