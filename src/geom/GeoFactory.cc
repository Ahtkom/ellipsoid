#include <geom/GeoFactory.h>

#include <geom/GeoCoordinate.h>
#include <geom/GeoCoordinateSequence.h>
#include <geom/GeoLineSegment.h>
#include <geom/GeoLineString.h>
#include <geom/GeoLinearRing.h>
#include <geom/GeoMultiLineString.h>
#include <geom/GeoMultiPolygon.h>
#include <geom/GeoPoint.h>
#include <geom/GeoPolygon.h>

namespace ep {
namespace geom {

extern GeoFactory gf;

GeoCoordinate GeoFactory::createCoordinate(double lon, double lat) {
  return {lon, lat};
}

GeoCoordinateSequence::Ptr
GeoFactory::createCoordinateSequence(std::vector<GeoCoordinate> &&coords) {
  return std::unique_ptr<GeoCoordinateSequence>(
      new GeoCoordinateSequence(std::move(coords)));
}

GeoPoint::Ptr GeoFactory::createPoint(GeoCoordinate &&coord) {
  return std::unique_ptr<GeoPoint>(new GeoPoint(std::move(coord)));
}

GeoLineSegment::Ptr GeoFactory::createLineSegment(GeoCoordinate &&from,
                                                  GeoCoordinate &&to) {
  return std::unique_ptr<GeoLineSegment>(new GeoLineSegment(
      createPoint(std::move(from)), createPoint(std::move(to))));
}

GeoLineSegment::Ptr
GeoFactory::createLineSegment(std::vector<GeoCoordinate> &&coords) {
  return createLineSegment(std::move(coords.front()), std::move(coords.back()));
}

GeoLineSegment::Ptr
GeoFactory::createLineSegment(GeoCoordinateSequence::Ptr &&cseq) {
  return std::unique_ptr<GeoLineSegment>(
      new GeoLineSegment(createPoint(std::move(cseq->coords_[0])),
                         createPoint(std::move(cseq->coords_[1]))));
}

GeoLineString::Ptr
GeoFactory::createLineString(GeoCoordinateSequence::Ptr &&cseq) {
  return std::unique_ptr<GeoLineString>(new GeoLineString(std::move(cseq)));
}

GeoLinearRing::Ptr
GeoFactory::createLinearRing(GeoCoordinateSequence::Ptr &&cseq) {
  // TODO: check whether it is closed
  return std::unique_ptr<GeoLinearRing>(new GeoLinearRing(std::move(cseq)));
}

GeoLinearRing::Ptr GeoFactory::createLinearRing(GeoLineString::Ptr &&ls) {
  // TODO
  // return std::unique_ptr<GeoLinearRing>(new GeoLinearRing(ls));
}

GeoPolygon::Ptr GeoFactory::createPolygon(GeoLinearRing::Ptr &&shell) {
  return std::unique_ptr<GeoPolygon>(new GeoPolygon(std::move(shell)));
}

GeoPolygon::Ptr
GeoFactory::createPolygon(GeoLinearRing::Ptr &&shell,
                          std::vector<GeoLinearRing::Ptr> &&holes) {
  return std::unique_ptr<GeoPolygon>(
      new GeoPolygon(std::move(shell), std::move(holes)));
}

GeoPolygon::Ptr
GeoFactory::createPolygon(std::vector<GeoLinearRing::Ptr> &&rings) {
  GeoLinearRing::Ptr shell = std::move(rings[0]);
  rings.erase(rings.begin());
  return createPolygon(std::move(shell), std::move(rings));
}

GeoMultiLineString::Ptr
GeoFactory::createMultiLineString(std::vector<GeoLineString::Ptr> &&lines) {
  return std::unique_ptr<GeoMultiLineString>(
      new GeoMultiLineString(std::move(lines)));
}

GeoMultiPolygon::Ptr
GeoFactory::createMultiPolygon(std::vector<GeoPolygon::Ptr> &&ps) {
  return std::unique_ptr<GeoMultiPolygon>(new GeoMultiPolygon(std::move(ps)));
}

} // namespace geom
} // namespace ep