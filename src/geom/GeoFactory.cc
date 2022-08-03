#include "geom/GeoFactory.h"

#include "geom/GeoCoordinate.h"
#include "geom/GeoCoordinateSequence.h"
#include "geom/GeoLineSegment.h"
#include "geom/GeoLineString.h"
#include "geom/GeoLinearRing.h"
#include "geom/GeoMultiLineString.h"
#include "geom/GeoMultiPolygon.h"
#include "geom/GeoPoint.h"
#include "geom/GeoPolygon.h"
#include "geom/GeoReferenceSystem.h"

namespace ep {
namespace geom {

GeoCoordinate
GeoFactory::createCoordinate(double lon, double lat, GeoReferenceSystem ref) {
  return {lon, lat};
}

GeoCoordinateSequence::Ptr
GeoFactory::createCoordinateSequence(
    std::vector<GeoCoordinate> &&coords, GeoReferenceSystem ref) {
  return std::unique_ptr<GeoCoordinateSequence>(
      new GeoCoordinateSequence(std::move(coords)));
}

GeoPoint::Ptr
GeoFactory::createPoint(GeoCoordinate &&coord, GeoReferenceSystem ref) {
  return std::unique_ptr<GeoPoint>(new GeoPoint(std::move(coord), ref));
}

// GeoLineSegment::Ptr
// GeoFactory::createLineSegment(
//     GeoCoordinate &&from, GeoCoordinate &&to, GeoReferenceSystem ref) {
//   return std::unique_ptr<GeoLineSegment>(new GeoLineSegment(
//       createPoint(std::move(from)), createPoint(std::move(to))));
// }

// GeoLineSegment::Ptr
// GeoFactory::createLineSegment(
//     std::vector<GeoCoordinate> &&coords, GeoReferenceSystem ref) {
//   return createLineSegment(std::move(coords.front()),
//   std::move(coords.back()));
// }

// GeoLineSegment::Ptr
// GeoFactory::createLineSegment(
//     GeoCoordinateSequence::Ptr &&cseq, GeoReferenceSystem ref) {
//   return std::unique_ptr<GeoLineSegment>(
//       new GeoLineSegment(createPoint(std::move(cseq->coords_[0])),
//           createPoint(std::move(cseq->coords_[1]))));
// }

GeoLineString::Ptr
GeoFactory::createLineString(
    GeoCoordinateSequence::Ptr &&cseq, GeoReferenceSystem ref) {
  return std::unique_ptr<GeoLineString>(
      new GeoLineString(std::move(cseq), ref));
}

GeoLinearRing::Ptr
GeoFactory::createLinearRing(
    GeoCoordinateSequence::Ptr &&cseq, GeoReferenceSystem ref) {
  // TODO: check whether it is closed
  return std::unique_ptr<GeoLinearRing>(
      new GeoLinearRing(std::move(cseq), ref));
}

GeoLinearRing::Ptr
GeoFactory::createLinearRing(GeoLineString::Ptr &&ls, GeoReferenceSystem ref) {
  // TODO
  // return std::unique_ptr<GeoLinearRing>(new GeoLinearRing(ls));
}

GeoPolygon::Ptr
GeoFactory::createPolygon(GeoLinearRing::Ptr &&shell, GeoReferenceSystem ref) {
  return std::unique_ptr<GeoPolygon>(new GeoPolygon(std::move(shell), ref));
}

GeoPolygon::Ptr
GeoFactory::createPolygon(GeoLinearRing::Ptr &&shell,
    std::vector<GeoLinearRing::Ptr> &&holes, GeoReferenceSystem ref) {
  return std::unique_ptr<GeoPolygon>(
      new GeoPolygon(std::move(shell), std::move(holes), ref));
}

GeoPolygon::Ptr
GeoFactory::createPolygon(
    std::vector<GeoLinearRing::Ptr> &&rings, GeoReferenceSystem ref) {
  GeoLinearRing::Ptr shell = std::move(rings[0]);
  rings.erase(rings.begin());
  return createPolygon(std::move(shell), std::move(rings), ref);
}

GeoMultiLineString::Ptr
GeoFactory::createMultiLineString(
    std::vector<GeoLineString::Ptr> &&lines, GeoReferenceSystem ref) {
  return std::unique_ptr<GeoMultiLineString>(
      new GeoMultiLineString(std::move(lines), ref));
}

GeoMultiPolygon::Ptr
GeoFactory::createMultiPolygon(
    std::vector<GeoPolygon::Ptr> &&ps, GeoReferenceSystem ref) {
  return std::unique_ptr<GeoMultiPolygon>(
      new GeoMultiPolygon(std::move(ps), ref));
}

} // namespace geom
} // namespace ep