#ifndef ELLIPSOID_IO_WKTWRITER_H_
#define ELLIPSOID_IO_WKTWRITER_H_

#include "geom/GeoGeometry.h"

#include <cstddef>
#include <memory>
#include <string>
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
namespace io {

class WKTWriter
{
public:
  WKTWriter(unsigned precision = 6);

  unsigned getPrecision() const;
  void     setPrecision(unsigned precision);

  std::vector<char> write(const geom::GeoGeometry *geometry);

private:
  std::vector<char> writePoint(const geom::GeoPoint *pt);

  std::vector<char> writeLineSegment(const geom::GeoLineSegment *seg);

  std::vector<char> writeLineString(const geom::GeoLineString *ls);

  std::vector<char> writeLinearRing(const geom::GeoLinearRing *lr);

  std::vector<char> writePolygon(const geom::GeoPolygon *p);

  std::vector<char> writeMultiLineString(const geom::GeoMultiLineString *mls);

  std::vector<char> writeMultiPolygon(const geom::GeoMultiPolygon *mp);

  char *writeCoordinateAt(char *pos, const geom::GeoCoordinate *c);

  char *writeCoordinateSequenceAt(
      char *pos, const geom::GeoCoordinateSequence *cseq);

private:
  unsigned precision_;
};

} // namespace io
} // namespace ep

#endif // ELLIPSOID_IO_WKTWRITER_H_