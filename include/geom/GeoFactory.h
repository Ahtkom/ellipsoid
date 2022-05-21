#ifndef ELLIPSOID_GEOM_GEOFACTORY_H_
#define ELLIPSOID_GEOM_GEOFACTORY_H_

#include <geom/GeoGeometry.h>

#include <memory>
#include <vector>

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
namespace geom {

/**
 * @brief Factory class used to create instances of geometry objects.
 */
class GeoFactory {
public:
  GeoFactory() = default;

  ~GeoFactory() = default;

  GeoCoordinate createCoordinate(double lon, double lat);

  std::unique_ptr<GeoCoordinateSequence>
  createCoordinateSequence(std::vector<GeoCoordinate> &&coords);

  std::unique_ptr<GeoPoint> createPoint(GeoCoordinate &&coord);

  std::unique_ptr<GeoLineSegment> createLineSegment(GeoCoordinate &&from,
                                                    GeoCoordinate &&to);

  std::unique_ptr<GeoLineSegment>
  createLineSegment(std::vector<GeoCoordinate> &&coords);

  std::unique_ptr<GeoLineSegment>
  createLineSegment(std::unique_ptr<GeoCoordinateSequence> &&cseq);

  std::unique_ptr<GeoLineString>
  createLineString(std::unique_ptr<GeoCoordinateSequence> &&cseq);

  std::unique_ptr<GeoLinearRing>
  createLinearRing(std::unique_ptr<GeoCoordinateSequence> &&cseq);

  std::unique_ptr<GeoLinearRing>
  createLinearRing(std::unique_ptr<GeoLineString> &&ls);

  std::unique_ptr<GeoPolygon>
  createPolygon(std::unique_ptr<GeoLinearRing> &&shell);

  std::unique_ptr<GeoPolygon>
  createPolygon(std::unique_ptr<GeoLinearRing> &&shell,
                std::vector<std::unique_ptr<GeoLinearRing>> &&holes);

  std::unique_ptr<GeoPolygon>
  createPolygon(std::vector<std::unique_ptr<GeoLinearRing>> &&rings);

  std::unique_ptr<GeoMultiLineString>
  createMultiLineString(std::vector<std::unique_ptr<GeoLineString>> &&lines);

  std::unique_ptr<GeoMultiPolygon>
  createMultiPolygon(std::vector<std::unique_ptr<GeoPolygon>> &&ps);
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_GEOFACTORY_H_