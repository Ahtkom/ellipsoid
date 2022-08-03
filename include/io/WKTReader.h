#ifndef ELLIPSOID_IO_WKTREADER_H_
#define ELLIPSOID_IO_WKTREADER_H_

#include "geom/GeoFactory.h"
#include "geom/GeoGeometry.h"
#include "geom/GeoReferenceSystem.h"

#include <memory>
#include <string>
#include <string_view>
#include <type_traits>

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

class WKTReader
{
public:
  explicit WKTReader(
      geom::GeoReferenceSystem ref = geom::GeoReferenceSystem::undefined);

  std::unique_ptr<geom::GeoGeometry> read(std::string_view wkt);

  // For specific geometry types.
  template <typename T>
  std::unique_ptr<T> read(std::string_view geojson_str) {
    static_assert(std::is_base_of_v<geom::GeoGeometry, T>);

    auto geometry = read(geojson_str);
    auto g        = dynamic_cast<const T *>(geometry.get());
    if (!g) {
      throw ParseException(
          __PRETTY_FUNCTION__, "Unsupported type for conversion!");
    }
    return std::unique_ptr<T>(static_cast<T *>(geometry.release()));
  }

  geom::GeoReferenceSystem getGeoReference() const;
  void                     setGeoReference(geom::GeoReferenceSystem ref);

private:
  // WKT form: x y
  geom::GeoCoordinate readCoordinate(std::string_view wkt);

  // WKT form: x1 y1,...,xn yn
  std::unique_ptr<geom::GeoCoordinateSequence> readCoordinateSequence(
      std::string_view wkt);

  // WKT form: x y
  std::unique_ptr<geom::GeoPoint> readPoint(std::string_view wkt);

  // WKT form: x1 y1,x2 y2
  std::unique_ptr<geom::GeoLineSegment> readLineSegment(std::string_view wkt);

  // WKT form: x1 y1,...,xn yn
  std::unique_ptr<geom::GeoLineString> readLineString(std::string_view wkt);

  // WKT form: x1 y1,...,xn yn,x1 y1
  std::unique_ptr<geom::GeoLinearRing> readLinearRing(std::string_view wkt);

  // WKT form:
  //  (x01 y01,...,x0n y0n,x01 y01),
  //  (x11 y11,...,x1n y1n,x11 y11),
  //  ...,
  //  (xm1 ym1,...,xmn ymn,xm1 ym1)
  std::unique_ptr<geom::GeoPolygon> readPolygon(std::string_view wkt);

  // WKT form:
  //  (x11 y11,...,x1n y1n),
  //  ...,
  //  (xm1 ym1,...,xmn ymn)
  std::unique_ptr<geom::GeoMultiLineString> readMultiLineString(
      std::string_view wkt);

  // WKT form:
  //  ((x011 y011,...,x0n1 y0n1,x011 y011)
  //   ...,
  //   (xm11 ym11,...,xmn1 ymn1,xm11 ym11)),
  //  ...,
  //  ((x01k y01k,...,x0nk y0nk,x01k y01k)
  //   ...,
  //   (xm1k ym1k,...,xmnk ymnk,xm1k ym1k)))
  std::unique_ptr<geom::GeoMultiPolygon> readMultiPolygon(std::string_view wkt);

  // return the index of first occurrence in `str` that equals the given token,
  // -1 if not found
  int findNextToken(std::string_view str, char token);

  // return the index of first occurrence of starting position, -1 if not found
  int findNextToken(std::string_view str, std::string_view token);

private:
  geom::GeoReferenceSystem refsys_;
};

} // namespace io
} // namespace ep

#endif // ELLIPSOID_IO_WKTREADER_H_