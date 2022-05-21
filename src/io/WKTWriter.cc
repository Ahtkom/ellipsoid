#include <io/WKTWriter.h>

#include <geom/GeoCoordinate.h>
#include <geom/GeoCoordinateSequence.h>
#include <geom/GeoLineSegment.h>
#include <geom/GeoLineString.h>
#include <geom/GeoLinearRing.h>
#include <geom/GeoMultiLineString.h>
#include <geom/GeoMultiPolygon.h>
#include <geom/GeoPoint.h>
#include <geom/GeoPolygon.h>

#include <memory>

namespace ep {
namespace io {

std::unique_ptr<WKTWriter> WKTWriter::getWriter() {
  return std::unique_ptr<WKTWriter>(new WKTWriter);
}

std::string WKTWriter::write(const geom::GeoGeometry *geometry) {
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

std::string WKTWriter::writePoint(const geom::GeoPoint *pt) {
  return pt->getGeometryType() + "(" + writeCoordinate(pt->getCoordinate()) +
         ")";
}

std::string WKTWriter::writeLineSegment(const geom::GeoLineSegment *seg) {
  return seg->getGeometryType() + "(" +
         writeCoordinate(seg->getFromPoint()->getCoordinate()) + "," +
         writeCoordinate(seg->getToPoint()->getCoordinate()) + ")";
}

std::string WKTWriter::writeLineString(const geom::GeoLineString *ls) {
  return ls->getGeometryType() + writeCoordinateSequence(ls->getCoordinates());
}

std::string WKTWriter::writeLinearRing(const geom::GeoLinearRing *lr) {
  return lr->getGeometryType() + writeCoordinateSequence(lr->getCoordinates());
}

std::string WKTWriter::writePolygon(const geom::GeoPolygon *p) {
  std::string wkt = p->getGeometryType() + "(" +
                    writeLinearRing(p->getExteriorRing()).substr(10);
  for (std::size_t i = 0; i != p->getNumInteriorRing(); ++i) {
    wkt += "," + writeLinearRing(p->getInteriorRingN(i)).substr(10);
  }
  wkt += ")";
  return wkt;
}

std::string
WKTWriter::writeMultiLineString(const geom::GeoMultiLineString *mls) {
  std::string wkt = mls->getGeometryType() + "(";
  std::size_t n = mls->getNumLineString();
  for (std::size_t i = 0; i != n - 1; ++i) {
    wkt += writeLineString(mls->getLineStringN(i)).substr(10) + ",";
  }
  wkt += writeLineString(mls->getLineStringN(n - 1)).substr(10) + ")";
  return wkt;
}

std::string WKTWriter::writeMultiPolygon(const geom::GeoMultiPolygon *mp) {
  std::string wkt = mp->getGeometryType() + "(";
  std::size_t n = mp->getNumPolygon();
  for (std::size_t i = 0; i != n - 1; ++i) {
    wkt += writePolygon(mp->getPolygonN(i)).substr(7) + ",";
  }
  wkt += writePolygon(mp->getPolygonN(n - 1)).substr(7) + ")";
  return wkt;
}

std::string WKTWriter::writeCoordinate(const geom::GeoCoordinate *c) {
  return std::to_string(c->getLon()) + " " + std::to_string(c->getLat());
}

std::string
WKTWriter::writeCoordinateSequence(const geom::GeoCoordinateSequence *cseq) {
  std::string wkt = "(";
  std::size_t n = cseq->getNumCoordinate();
  wkt.reserve(32 * n);
  for (std::size_t i = 0; i != n - 1; ++i) {
    wkt += writeCoordinate(cseq->getCoordinateN(i)) + ",";
  }
  wkt += writeCoordinate(cseq->getCoordinateN(n - 1)) + ")";
  return wkt;
}

} // namespace io
} // namespace ep