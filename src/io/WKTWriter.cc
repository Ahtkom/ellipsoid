#include "io/WKTWriter.h"

#include "geom/GeoCoordinate.h"
#include "geom/GeoCoordinateSequence.h"
#include "geom/GeoLineSegment.h"
#include "geom/GeoLineString.h"
#include "geom/GeoLinearRing.h"
#include "geom/GeoMultiLineString.h"
#include "geom/GeoMultiPolygon.h"
#include "geom/GeoPoint.h"
#include "geom/GeoPolygon.h"

#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace ep {
namespace io {

WKTWriter::WKTWriter(unsigned precision)
    : precision_(precision) { }

unsigned
WKTWriter::getPrecision() const {
  return precision_;
}

void
WKTWriter::setPrecision(unsigned precision) {
  precision_ = precision;
}

std::vector<char>
WKTWriter::write(const geom::GeoGeometry *geometry) {
  std::string geomType = geometry->getGeometryType();
  if (geomType == "POINT") {
    return writePoint(static_cast<const geom::GeoPoint *>(geometry));
  } else if (geomType == "LINESEGMENT") {
    return writeLineSegment(
        static_cast<const geom::GeoLineSegment *>(geometry));
  } else if (geomType == "LINESTRING") {
    return writeLineString(static_cast<const geom::GeoLineString *>(geometry));
  } else if (geomType == "LINEARRING") {
    return writeLinearRing(static_cast<const geom::GeoLinearRing *>(geometry));
  } else if (geomType == "POLYGON") {
    return writePolygon(static_cast<const geom::GeoPolygon *>(geometry));
  } else if (geomType == "MULTILINESTRING") {
    return writeMultiLineString(
        static_cast<const geom::GeoMultiLineString *>(geometry));
  } else {
    return writeMultiPolygon(
        static_cast<const geom::GeoMultiPolygon *>(geometry));
  }
}

std::vector<char>
WKTWriter::writePoint(const geom::GeoPoint *pt) {
  std::vector<char> buffer(2 * getPrecision() + 17);

  auto pos = buffer.data();
  pos += std::sprintf(pos, "POINT(");
  pos  = writeCoordinateAt(pos, pt->getCoordinate());
  *pos = ')';
  return buffer;
}

std::vector<char>
WKTWriter::writeLineSegment(const geom::GeoLineSegment *seg) {
  std::vector<char> buffer(4 * getPrecision() + 33);

  auto pos = buffer.data();
  pos += std::sprintf(pos, "LINESEGMENT(");
  pos    = writeCoordinateAt(pos, seg->getFromCoordinate());
  *pos++ = ',';
  pos    = writeCoordinateAt(pos, seg->getToCoordinate());
  *pos   = ')';
  return buffer;
}

std::vector<char>
WKTWriter::writeLineString(const geom::GeoLineString *ls) {
  std::size_t capacity =
      (2 * getPrecision() + 10) * ls->getCoordinates()->getNumCoordinate() + 12;
  std::vector<char> buffer(capacity);

  auto pos = buffer.data();
  pos += std::sprintf(pos, "LINESTRING");
  pos = writeCoordinateSequenceAt(pos, ls->getCoordinates());
  return buffer;
}

std::vector<char>
WKTWriter::writeLinearRing(const geom::GeoLinearRing *lr) {
  std::size_t capacity =
      (2 * getPrecision() + 10) * lr->getNumCoordinate() + 12;
  std::vector<char> buffer(capacity);

  auto pos = buffer.data();
  pos += std::sprintf(pos, "LINEARRING");
  pos = writeCoordinateSequenceAt(pos, lr->getCoordinates());
  return buffer;
}

std::vector<char>
WKTWriter::writePolygon(const geom::GeoPolygon *p) {
  std::size_t capacity =
      (2 * getPrecision() + 10) * p->getExteriorRing()->getNumCoordinate() + 11;
  for (std::size_t i = 0; i != p->getNumInteriorRing(); ++i) {
    capacity +=
        (2 * getPrecision() + 10) * p->getInteriorRing(i)->getNumCoordinate() +
        2;
  }
  std::vector<char> buffer(capacity);

  auto pos = buffer.data();
  pos += std::sprintf(pos, "POLYGON(");
  pos = writeCoordinateSequenceAt(pos, p->getExteriorRing()->getCoordinates());
  pos += std::sprintf(pos, ",");
  for (std::size_t i = 0; i != p->getNumInteriorRing(); ++i) {
    pos =
        writeCoordinateSequenceAt(pos, p->getInteriorRing(i)->getCoordinates());
    pos += std::sprintf(pos, ",");
  }
  *(pos - 1) = ')';
  *pos       = '\0';
  return buffer;
}

std::vector<char>
WKTWriter::writeMultiLineString(const geom::GeoMultiLineString *mls) {
  std::size_t capacity = 17;
  for (std::size_t i = 0; i != mls->getNumLineString(); ++i) {
    capacity +=
        (2 * getPrecision() + 10) * mls->getLineString(i)->getNumCoordinate() +
        2;
  }
  std::vector<char> buffer(capacity);

  auto pos = buffer.data();
  pos += std::sprintf(pos, "MULTILINESTRING(");
  for (std::size_t i = 0; i != mls->getNumLineString(); ++i) {
    pos =
        writeCoordinateSequenceAt(pos, mls->getLineString(i)->getCoordinates());
    pos += std::sprintf(pos, ",");
  }
  *(pos - 1) = ')';
  *pos       = '\0';
  return buffer;
}

std::vector<char>
WKTWriter::writeMultiPolygon(const geom::GeoMultiPolygon *mp) {
  std::size_t capacity = 14;
  for (std::size_t i = 0; i != mp->getNumPolygon(); ++i) {
    capacity += (2 * getPrecision() + 10) *
                    mp->getPolygon(i)->getExteriorRing()->getNumCoordinate() +
                4;
    for (std::size_t j = 0; j != mp->getPolygon(i)->getNumInteriorRing(); ++j) {
      capacity +=
          (2 * getPrecision() + 10) *
              mp->getPolygon(i)->getInteriorRing(j)->getNumCoordinate() +
          2;
    }
  }
  std::vector<char> buffer(capacity);

  auto pos = buffer.data();
  pos += std::sprintf(pos, "MULTIPOLYGON((");
  for (std::size_t i = 0; i != mp->getNumPolygon(); ++i) {
    pos = writeCoordinateSequenceAt(
        pos, mp->getPolygon(i)->getExteriorRing()->getCoordinates());
    pos += std::sprintf(pos, ",");
    for (std::size_t j = 0; j != mp->getPolygon(i)->getNumInteriorRing(); ++j) {
      pos = writeCoordinateSequenceAt(
          pos, mp->getPolygon(i)->getInteriorRing(j)->getCoordinates());
      pos += std::sprintf(pos, ",");
    }
    *(pos - 1) = ')';
    pos += std::sprintf(pos, ",(");
  }
  *(pos - 2) = ')';
  *(pos - 1) = '\0';
  return buffer;
}

char *
WKTWriter::writeCoordinateAt(char *pos, const geom::GeoCoordinate *c) {
  char format[12];
  std::sprintf(format, "%%.%dlf %%.%dlf", getPrecision(), getPrecision());
  pos += std::sprintf(pos, format, c->getLon(), c->getLat());
  return pos;
}

char *
WKTWriter::writeCoordinateSequenceAt(
    char *pos, const geom::GeoCoordinateSequence *cseq) {
  char format[13];
  std::sprintf(format, "%%.%dlf %%.%dlf,", getPrecision(), getPrecision());

  *pos++ = '(';
  for (std::size_t i = 0; i != cseq->getNumCoordinate(); ++i) {
    auto c = cseq->getCoordinate(i);
    pos += std::sprintf(pos, format, c->getLon(), c->getLat());
  }
  *(pos - 1) = ')';

  return pos;
}

} // namespace io
} // namespace ep