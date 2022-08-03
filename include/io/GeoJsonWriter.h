#ifndef ELLIPSOID_IO_GEOJSONWRITER_H_
#define ELLIPSOID_IO_GEOJSONWRITER_H_

#include <geom/GeoGeometry.h>
#include <memory>
#include <string>
#include <vend/json.hpp>


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
namespace io {

class GeoJsonWriter
{
public:
  static std::unique_ptr<GeoJsonWriter> getWriter();

  GeoJsonWriter() = default;

  ~GeoJsonWriter() = default;

  std::string write(const geom::GeoGeometry *geometry);

private:
  std::string writePoint(const geom::GeoPoint *pt);

  std::string writeLineSegment(const geom::GeoLineSegment *seg);

  std::string writeLineString(const geom::GeoLineString *ls);

  std::string writeLinearRing(const geom::GeoLinearRing *lr);

  std::string writePolygon(const geom::GeoPolygon *p);

  std::string writeMultiLineString(const geom::GeoMultiLineString *mls);

  std::string writeMultiPolygon(const geom::GeoMultiPolygon *mp);

  nlohmann::json writePointAsJson(const geom::GeoPoint *pt);

  nlohmann::json writeLineSegmentAsJson(const geom::GeoLineSegment *seg);

  nlohmann::json writeLineStringAsJson(const geom::GeoLineString *ls);

  nlohmann::json writeLinearRingAsJson(const geom::GeoLinearRing *lr);

  nlohmann::json writePolygonAsJson(const geom::GeoPolygon *p);

  nlohmann::json writeMultiLineStringAsJson(
      const geom::GeoMultiLineString *mls);

  nlohmann::json writeMultiPolygonAsJson(const geom::GeoMultiPolygon *mp);

  nlohmann::json writeCoordinateAsJson(const geom::GeoCoordinate *c);

  nlohmann::json writeCoordinateSequenceAsJson(
      const geom::GeoCoordinateSequence *cseq);
};

} // namespace io
} // namespace ep

#endif // ELLIPSOID_IO_GEOJSONWRITER_H_