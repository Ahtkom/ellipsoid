#ifndef ELLIPSOID_OP_METRIC_LENGTHMETRIC_H_
#define ELLIPSOID_OP_METRIC_LENGTHMETRIC_H_

#include <geom/GeoEarth.h>
#include <geom/GeoGeometry.h>
#include <op/metric/BaseMetric.h>
#include <op/metric/DistanceMetric.h>

#include <memory>

namespace ep {
namespace geom {
class GeoLineSegment;
class GeoLineString;
class GeoLinearRing;
// class GeoPolygon;
class GeoMultiLineString;
// class GeoMultiPolygon;
} // namespace geom
} // namespace ep

namespace ep {
namespace op {

class LengthMetric : public BaseMetric {
public:
  LengthMetric(const geom::GeoEarth &earth);

  ~LengthMetric() override = default;

  double evaluateLength(const geom::GeoGeometry *geometry);

private:
  double lengthOfLineSegment(const geom::GeoLineSegment *seg);

  double lengthOfLineString(const geom::GeoLineString *ls);

  // double lengthOfPolygon(const geom::GeoPolygon *p);

  double lengthOfMultiLineString(const geom::GeoMultiLineString *mls);

  // double lengthOfMultiPolygon(const geom::GeoMultiPolygon *mp);

private:
  std::unique_ptr<DistanceMetric> dm;
};

} // namespace op
} // namespace ep

#endif // ELLIPSOID_OP_METRIC_LENGTHMETRIC_H_