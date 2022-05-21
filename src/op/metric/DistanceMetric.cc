#include <algorithm/metric/BesselSecondTheme.h>
#include <geom/GeoCoordinate.h>
#include <geom/GeoCoordinateSequence.h>
#include <geom/GeoFactory.h>
#include <geom/GeoLineSegment.h>
#include <geom/GeoLineString.h>
#include <geom/GeoLinearRing.h>
#include <geom/GeoMultiLineString.h>
#include <geom/GeoMultiPolygon.h>
#include <geom/GeoPoint.h>
#include <geom/GeoPolygon.h>
#include <op/metric/DistanceMetric.h>

#include <iostream>

namespace ep {
namespace op {

DistanceMetric::DistanceMetric(const geom::GeoEarth &earth)
    : BaseMetric(earth), st(new alg::BesselSecondTheme()) {}

DistanceMetric::DistanceMetric(const geom::GeoEarth &earth,
                               std::unique_ptr<alg::SecondTheme> &&second_theme)
    : BaseMetric(earth), st(std::move(second_theme)) {}

void DistanceMetric::setSecondTheme(
    std::unique_ptr<alg::SecondTheme> &&second_theme) {
  st = std::move(second_theme);
}

void DistanceMetric::setGeoEarth(const geom::GeoEarth &earth) {
  BaseMetric::setGeoEarth(earth);
  st->setGeoEarth(earth);
}

double DistanceMetric::distance(const geom::GeoGeometry *g1,
                                const geom::GeoGeometry *g2) {
  if (g1->getGeometryType() == "POINT") {
    if (g2->getGeometryType() == "POINT") {
      return distanceBetweenPoints(static_cast<const geom::GeoPoint *>(g1),
                                   static_cast<const geom::GeoPoint *>(g2));
    }
  }
  return -1.0;
  // if (g1->getGeometryType() == "POINT") {
  //     if (g2->getGeometryType() == "POINT") {
  //         return distancePoints(
  // 			static_cast<const geom::GeoPoint *>(g1),
  // 			static_cast<const geom::GeoPoint *>(g2));
  //     } else if (g2->getGeometryType() == "LINESTRING" ||
  // 			g2->getGeometryType() == "LINEARRING") {
  // 		return distancePointToLineString(
  // 			static_cast<const geom::GeoPoint *>(g1),
  // 			static_cast<const geom::GeoLineString *>(g2));
  // 	} else if (g2->getGeometryType() == "POLYGON") {
  // 		return distancePointToPolygon(
  // 			static_cast<const geom::GeoPoint *>(g1),
  // 			static_cast<const geom::GeoPolygon *>(g2));
  // 	} else if (g2->getGeometryType() == "MULTILINESTRING") {
  // 		return distancePointToMultiLineString(
  // 			static_cast<const geom::GeoPoint *>(g1),
  // 			static_cast<const geom::GeoMultiLineString *>(g2));
  // 	} else if (g2->getGeometryType() == "MULTIPolygon") {
  // 		return distancePointToMultiPolygon(
  // 			static_cast<const geom::GeoPoint *>(g1),
  // 			static_cast<const geom::GeoMultiPolygon *>(g2));
  // 	}
  // } else if (g1->getGeometryType() == "LINESTRING") {
  // 	if (g2->getGeometryType() == "LINESTRING" ||
  // 			g2->getGeometryType() == "LINEARRING") {
  // 		return distanceLineStrings(
  // 			static_cast<const geom::GeoLineString *>(g1),
  // 			static_cast<const geom::GeoLineString *>(g2));
  // 	} else if (g2->getGeometryType() == "POLYGON") {
  // 		return distanceLineStringToPolygon(
  // 			static_cast<const geom::GeoLineString *>(g1),
  // 			static_cast<const geom::GeoPolygon *>(g2));
  // 	} else if (g2->getGeometryType() == "MULTILINESTRING") {
  // 		return distanceLineStringToMultiLineString(
  // 			static_cast<const geom::GeoLineString *>(g1),
  // 			static_cast<const geom::GeoMultiLineString *>(g2));
  // 	} else if (g2->getGeometryType() == "MULTIPOLYGON") {
  // 		return distanceLineStringToMultiPolygon(
  // 			static_cast<const geom::GeoLineString *>(g1),
  // 			static_cast<const geom::GeoMultiPolygon *>(g2));
  // 	}
  // } else if (g1->getGeometryType() == "POLYGON") {
  // 	if (g2->getGeometryType() == "POLYGON") {
  // 		return distancePolygons(
  // 			static_cast<const geom::GeoPolygon *>(g1),
  // 			static_cast<const geom::GeoPolygon *>(g2));
  // 	} else if (g2->getGeometryType() == "MULTILINESTRING") {
  // 		return distancePolygonToMultiLineString(
  // 			static_cast<const geom::GeoPolygon *>(g1),
  // 			static_cast<const geom::GeoMultiLineString *>(g2));
  // 	} else if (g2->getGeometryType() == "MULTIPOLYGON") {
  // 		return distancePolygonToMultiPolygon(
  // 			static_cast<const geom::GeoPolygon *>(g1),
  // 			static_cast<const geom::GeoMultiPolygon *>(g2));
  // 	}
  // } else if (g1->getGeometryType() == "MULTILINESTRING") {
  // 	if (g2->getGeometryType() == "MULTILINESTRING") {
  // 		return distanceMultiLineStrings(
  // 			static_cast<const geom::GeoMultiLineString *>(g1),
  // 			static_cast<const geom::GeoMultiLineString *>(g2));
  // 	} else if (g2->getGeometryType() == "MULTIPOLYGON") {
  // 		return distanceMultiLineStringToMultiPolygon(
  // 			static_cast<const geom::GeoMultiLineString *>(g1),
  // 			static_cast<const geom::GeoMultiPolygon *>(g2));
  // 	}
  // } else if (g1->getGeometryType() == "MULTIPOLYGON") {
  // 	if (g2->getGeometryType() == "MULTIPOLYGON") {
  // 		return distanceMultiPolygons(
  // 			static_cast<const geom::GeoMultiPolygon *>(g1),
  // 			static_cast<const geom::GeoMultiPolygon *>(g2));
  // 	}
  // }
  // return evaluateDistance(g2, g1);
}

// double
// DistanceMetric::distancePointToLineString
//  (const geom::GeoPoint *pt, const geom::GeoLineString *ls)
// {
// }

double DistanceMetric::distanceBetweenPoints(const geom::GeoPoint *pt1,
                                             const geom::GeoPoint *pt2) {
  return distanceBetweenCoordinates(pt1->getCoordinate(), pt2->getCoordinate());
}

double
DistanceMetric::distanceBetweenCoordinates(const geom::GeoCoordinate *coord1,
                                           const geom::GeoCoordinate *coord2) {
  double res = st->evaluateDistance(coord1, coord2);

#ifdef ELLIPSOID_DEBUG
  // std::cout << "DistanceMetric::distanceCoordinates\n"
  //   << a1 << " " << a2 << std::endl;
#endif

  return std::abs(res);
}

} // namespace op
} // namespace ep