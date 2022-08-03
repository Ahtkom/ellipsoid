#include <io/GeoJsonWriter.h>

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

std::unique_ptr<GeoJsonWriter> GeoJsonWriter::getWriter() {
  return std::unique_ptr<GeoJsonWriter>(new GeoJsonWriter);
}

std::string GeoJsonWriter::write(const geom::GeoGeometry *geometry) {
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

std::string GeoJsonWriter::writePoint(const geom::GeoPoint *pt) {
  return writePointAsJson(pt).dump();
}

std::string GeoJsonWriter::writeLineSegment(const geom::GeoLineSegment *seg) {
  return writeLineSegmentAsJson(seg).dump();
}

std::string GeoJsonWriter::writeLineString(const geom::GeoLineString *ls) {
  return writeLineStringAsJson(ls).dump();
}

std::string GeoJsonWriter::writeLinearRing(const geom::GeoLinearRing *lr) {
  return writeLinearRingAsJson(lr).dump();
}

std::string GeoJsonWriter::writePolygon(const geom::GeoPolygon *p) {
  return writePolygonAsJson(p).dump();
}

std::string
GeoJsonWriter::writeMultiLineString(const geom::GeoMultiLineString *mls) {
  return writeMultiLineStringAsJson(mls).dump();
}

std::string GeoJsonWriter::writeMultiPolygon(const geom::GeoMultiPolygon *mp) {
  return writeMultiPolygonAsJson(mp).dump();
}

nlohmann::json GeoJsonWriter::writePointAsJson(const geom::GeoPoint *pt) {
  nlohmann::json json;
  json["type"] = "Point";
  json["coordinates"] = writeCoordinateAsJson(pt->getCoordinate());
  return json;
}

nlohmann::json
GeoJsonWriter::writeLineSegmentAsJson(const geom::GeoLineSegment *seg) {
  nlohmann::json json;
  json["type"] = "LineSegment";
  json["coordinates"][0] =
      writeCoordinateAsJson(seg->getFromPoint()->getCoordinate());
  json["coordinates"][1] =
      writeCoordinateAsJson(seg->getToPoint()->getCoordinate());
  return json;
}

nlohmann::json
GeoJsonWriter::writeLineStringAsJson(const geom::GeoLineString *ls) {
  nlohmann::json json;
  json["type"] = "LineString";
  json["coordinates"] = writeCoordinateSequenceAsJson(ls->getCoordinates());
  return json;
}

nlohmann::json
GeoJsonWriter::writeLinearRingAsJson(const geom::GeoLinearRing *lr) {
  nlohmann::json json;
  json["type"] = "LinearRing";
  json["coordinates"] = writeCoordinateSequenceAsJson(lr->getCoordinates());
  return json;
}

nlohmann::json GeoJsonWriter::writePolygonAsJson(const geom::GeoPolygon *p) {
  nlohmann::json json;
  json["type"] = "Polygon";
  json["coordinates"][0] =
      writeLinearRingAsJson(p->getExteriorRing())["coordinates"];
  for (std::size_t i = 0; i != p->getNumInteriorRing(); ++i) {
    json["coordinates"][i + 1] =
        writeLinearRingAsJson(p->getInteriorRing(i))["coordinates"];
  }
  return json;
}

nlohmann::json
GeoJsonWriter::writeMultiLineStringAsJson(const geom::GeoMultiLineString *mls) {
  nlohmann::json json;
  json["type"] = "MultiLineString";
  for (std::size_t i = 0; i != mls->getNumLineString(); ++i) {
    json["coordinates"][i] =
        writeLineStringAsJson(mls->getLineString(i))["coordinates"];
  }
  return json;
}

nlohmann::json
GeoJsonWriter::writeMultiPolygonAsJson(const geom::GeoMultiPolygon *mp) {
  nlohmann::json json;
  json["type"] = "MultiPolygon";
  for (std::size_t i = 0; i != mp->getNumPolygon(); ++i) {
    json["coordinates"][i] =
        writePolygonAsJson(mp->getPolygon(i))["coordinates"];
  }
  return json;
}

nlohmann::json
GeoJsonWriter::writeCoordinateAsJson(const geom::GeoCoordinate *c) {
  return {c->getLon(), c->getLat()};
}

nlohmann::json GeoJsonWriter::writeCoordinateSequenceAsJson(
    const geom::GeoCoordinateSequence *cseq) {
  nlohmann::json json;
  for (std::size_t i = 0; i != cseq->getNumCoordinate(); ++i) {
    json[i] = writeCoordinateAsJson(cseq->getCoordinateN(i));
  }
  return json;
}

} // namespace io
} // namespace ep