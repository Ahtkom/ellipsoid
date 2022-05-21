#ifndef ELLIPSOID_IO_GEOJSONREADER_H_
#define ELLIPSOID_IO_GEOJSONREADER_H_

#include <geom/GeoFactory.h>
#include <geom/GeoGeometry.h>
#include <io/ParseException.h>
#include <vend/json.hpp>

#include <memory>
#include <string>
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

class GeoJsonReader {
public:
  GeoJsonReader() = default;

  ~GeoJsonReader() = default;

  /**
   * @brief Parse a GeoJson string returning a geometry pointer.
   *
   */
  std::unique_ptr<geom::GeoGeometry> read(const std::string &geojson_str);

  /**
   * @brief Parse a GeoJson string returning a geometry pointer with specific
   *        type.
   *
   * @tparam T geometry types
   */
  template <typename T, typename = std::enable_if_t<
                            std::is_base_of<geom::GeoGeometry, T>::value>>
  std::unique_ptr<T> read(const std::string &geojson_str) {
    auto geometry = read(geojson_str);
    auto g = dynamic_cast<const T *>(geometry.get());
    if (!g) {
      throw ParseException(__PRETTY_FUNCTION__,
                           "Unsupported type for conversion!");
    }
    return std::unique_ptr<T>(static_cast<T *>(geometry.release()));
  }

protected:
  std::unique_ptr<geom::GeoGeometry> read(const nlohmann::json &geojson);

  std::unique_ptr<geom::GeoGeometry>
  readGeometryCoordinates(const nlohmann::json &geojson);

private:
  // GeoJson form: [x,y]
  geom::GeoCoordinate readCoordinate(const nlohmann::json &geojson);

  // GeoJson form: [[x1,y1],...,[xn,yn]]
  std::unique_ptr<geom::GeoCoordinateSequence>
  readCoordinateSequence(const nlohmann::json &geojson);

  // GeoJson form: [x,y]
  std::unique_ptr<geom::GeoPoint> readPoint(const nlohmann::json &geojson);

  // GeoJson form: [[x1,y1],[x2,y2]]
  std::unique_ptr<geom::GeoLineSegment>
  readLineSegment(const nlohmann::json &geojson);

  // GeoJson form: [[x1,y1],...,[xn,yn]]
  std::unique_ptr<geom::GeoLineString>
  readLineString(const nlohmann::json &geojson);

  // GeoJson form: [[x1,y1],...,[xn,yn],[x1,y1]]
  std::unique_ptr<geom::GeoLinearRing>
  readLinearRing(const nlohmann::json &geojson);

  // GeoJson form:
  //  [[[x01,y01],...,[x0n,y0n],[x01,y01]],
  //   [[x11,y11],...,[x1n,y1n],[x11,y11]],
  //   ...,
  //   [[xm1,ym1],...,[xmn,ymn],[xm1,ym1]]]
  std::unique_ptr<geom::GeoPolygon> readPolygon(const nlohmann::json &geojson);

  // GeoJson form:
  //  [[[x01,y01],...,[x0n,y0n]],
  //   [[x11,y11],...,[x1n,y1n]],
  //   ...,
  //   [[xm1,ym1],...,[xmn,ymn]]]
  std::unique_ptr<geom::GeoMultiLineString>
  readMultiLineString(const nlohmann::json &geojson);

  // GeoJson form:
  //  [[[[x011,y011],...,[x0n1,y0n1],[x011,y011]],
  //    ...,
  //    [[xm11,ym11],...,[xmn1,ymn1],[xm11,ym11]]],
  //   ...,
  //   [[[x01k,y01k],...,[x0nk,y0nk],[x01k,y01k]],
  //    ...,
  //    [[xm1k,ym1k],...,[xmnk,ymnk],[xm1k,ym1k]]]]
  std::unique_ptr<geom::GeoMultiPolygon>
  readMultiPolygon(const nlohmann::json &geojson);

private:
  geom::GeoFactory gf;
};

} // namespace io
} // namespace ep

#endif // ELLIPSOID_IO_GEOJSONREADER_H_