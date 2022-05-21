#ifndef ELLIPSOID_OP_METRIC_DISTANCEMETRIC_H_
#define ELLIPSOID_OP_METRIC_DISTANCEMETRIC_H_

#include <algorithm/metric/SecondTheme.h>
#include <geom/GeoEarth.h>
#include <geom/GeoGeometry.h>
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
} // namespace geom
} // namespace ep

namespace ep {
namespace op {

/**
 * @brief Provide metric calculation for distance, mainly based on some
 *        \b second-theme algorithms, default to \b Bessel-Second-Theme
 */
class DistanceMetric : public BaseMetric {
  friend class LengthMetric;

public:
  explicit DistanceMetric(const geom::GeoEarth &earth);

  DistanceMetric(const geom::GeoEarth &earth,
                 std::unique_ptr<alg::SecondTheme> &&second_theme);

  ~DistanceMetric() override = default;

  void setSecondTheme(std::unique_ptr<alg::SecondTheme> &&second_theme);

  void setGeoEarth(const geom::GeoEarth &earth) override;

  double distance(const geom::GeoGeometry *g1, const geom::GeoGeometry *g2);

protected:
  double distanceBetweenCoordinates(const geom::GeoCoordinate *coord1,
                                    const geom::GeoCoordinate *coord2);

  double distanceBetweenPoints(const geom::GeoPoint *pt1,
                               const geom::GeoPoint *pt2);

  // double distancePointToLineString
  //  (const geom::GeoPoint *pt, const geom::GeoLineString *ls);

  // double distancePointToPolygon
  //  (const geom::GeoPoint *pt, const geom::GeoPolygon *p);

  // double distancePointToMultiLineString
  //  (const geom::GeoPoint *pt, const geom::GeoMultiLineString *mls);

  // double distancePointToMultiPolygon
  //  (const geom::GeoPoint *pt, const geom::GeoMultiPolygon *mp);

  // double distanceLineStrings
  //  (const geom::GeoLineString *ls1, const geom::GeoLineString *ls2);

  // double distanceLineStringToPolygon
  //  (const geom::GeoLineString *ls, const geom::GeoPolygon *p);

  // double distanceLineStringToMultiLineString
  //  (const geom::GeoLineString *ls, const geom::GeoMultiLineString *mls);

  // double distanceLineStringToMultiPolygon
  //  (const geom::GeoLineString *ls, const geom::GeoMultiPolygon *mp);

  // double distancePolygons
  //  (const geom::GeoPolygon *p1, const geom::GeoPolygon *p2);

  // double distancePolygonToMultiLineStrin
  //  (const geom::GeoPolygon *p, const geom::GeoMultiLineString *mls);

  // double distancePolygonToMultiPolygon
  //  (const geom::GeoPolygon *p, const geom::GeoMultiPolygon *mp);

  // double distanceMultiLineStrings(
  //     const geom::GeoMultiLineString *mls1,
  //     const geom::GeoMultiLineString *mls2);

  // double distanceMultiLineStringToMultiPolygon
  //  (const geom::GeoMultiLineString *mls, const geom::GeoMultiPolygon *mp);

  // double distanceMultiPolygons
  //  (const geom::GeoMultiPolygon *mp1, const geom::GeoMultiPolygon *mp2);

  // double distanceCoordinateToTwoCoordinates(
  //     const geom::GeoCoordinate *coord,
  //     const geom::GeoCoordinate *coord1,
  //     const geom::GeoCoordinate *coord2);

  // double distanceCoordinateToCoordinateSequence(
  //     const geom::GeoCoordinate *coord,
  //     const geom::GeoCoordinateSequence *cseq);

  // double distanceCoordinateSequences(
  //     const geom::GeoCoordinateSequence *cseq1,
  //     const geom::GeoCoordinateSequence *cseq2);

private:
  std::unique_ptr<alg::SecondTheme> st;
};

} // namespace op
} // namespace ep

#endif // ELLIPSOID_OP_METRIC_DISTANCEMETRIC_H_