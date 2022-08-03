#include "io/WKTReader.h"

#include "geom/GeoCoordinate.h"
#include "geom/GeoCoordinateSequence.h"
#include "geom/GeoFactory.h"
#include "geom/GeoLineSegment.h"
#include "geom/GeoLineString.h"
#include "geom/GeoLinearRing.h"
#include "geom/GeoMultiLineString.h"
#include "geom/GeoMultiPolygon.h"
#include "geom/GeoPoint.h"
#include "geom/GeoPolygon.h"
#include "io/ParseException.h"

#include <cstddef>
#include <iostream>
#include <string_view>

namespace ep {
namespace io {

WKTReader::WKTReader(geom::GeoReferenceSystem ref)
    : refsys_(ref) { }

geom::GeoGeometry::Ptr
WKTReader::read(std::string_view wkt) {
  std::size_t n = wkt.size();
  if (n >= 10) {
    if (wkt.substr(0, 5) == "POINT") {
      return wkt.at(5) == ' ' ? readPoint(wkt.substr(7))
                              : readPoint(wkt.substr(6));
    } else if (wkt.substr(0, 11) == "LINESEGMENT") {
      return wkt.at(11) == ' ' ? readLineSegment(wkt.substr(13, n - 14))
                               : readLineSegment(wkt.substr(12, n - 13));
    } else if (wkt.substr(0, 10) == "LINESTRING") {
      return wkt.at(10) == ' ' ? readLineString(wkt.substr(12, n - 14))
                               : readLineString(wkt.substr(11, n - 12));
    } else if (wkt.substr(0, 10) == "LINEARRING") {
      return wkt.at(10) == ' ' ? readLinearRing(wkt.substr(12, n - 14))
                               : readLinearRing(wkt.substr(11, n - 12));
    } else if (wkt.substr(0, 7) == "POLYGON") {
      return wkt.at(7) == ' ' ? readPolygon(wkt.substr(9, n - 10))
                              : readPolygon(wkt.substr(8, n - 9));
    } else if (wkt.substr(0, 15) == "MULTILINESTRING") {
      return wkt.at(15) == ' ' ? readMultiLineString(wkt.substr(17, n - 18))
                               : readMultiLineString(wkt.substr(16, n - 17));
    } else if (wkt.substr(0, 12) == "MULTIPOLYGON") {
      return wkt.at(12) == ' ' ? readMultiPolygon(wkt.substr(14, n - 15))
                               : readMultiPolygon(wkt.substr(13, n - 14));
    }
  }
  throw ParseException(__PRETTY_FUNCTION__, "Invalid WKT form!");
}

geom::GeoReferenceSystem
WKTReader::getGeoReference() const {
  return refsys_;
}

void
WKTReader::setGeoReference(geom::GeoReferenceSystem ref) {
  refsys_ = ref;
}

geom::GeoPoint::Ptr
WKTReader::readPoint(std::string_view wkt) {
  return geom::GeoFactory::createPoint(readCoordinate(wkt), getGeoReference());
}

geom::GeoLineSegment::Ptr
WKTReader::readLineSegment(std::string_view wkt) {
  // return geom::GeoFactory::createLineSegment(readCoordinateSequence(wkt));
}

geom::GeoLineString::Ptr
WKTReader::readLineString(std::string_view wkt) {
  return geom::GeoFactory::createLineString(
      readCoordinateSequence(wkt), getGeoReference());
}

geom::GeoLinearRing::Ptr
WKTReader::readLinearRing(std::string_view wkt) {
  return geom::GeoFactory::createLinearRing(
      readCoordinateSequence(wkt), getGeoReference());
}

geom::GeoPolygon::Ptr
WKTReader::readPolygon(std::string_view wkt) {
  std::vector<geom::GeoLinearRing::Ptr> rings;

  int i = 1, len = wkt.size(), n;
  do {
    n = findNextToken(wkt.substr(i), ')');
    if (n == -1) {
      break;
    }
    rings.push_back(readLinearRing(wkt.substr(i, n)));
    i += n + 3;
  } while (i <= len);
  return geom::GeoFactory::createPolygon(std::move(rings), getGeoReference());
}

geom::GeoMultiLineString::Ptr
WKTReader::readMultiLineString(std::string_view wkt) {
  std::vector<geom::GeoLineString::Ptr> lines;

  int i = 1, len = wkt.size();
  while (int n = findNextToken(wkt.substr(i), ')') + 1) {
    lines.push_back(readLineString(wkt.substr(i, n - 1)));
    if ((i += n + 2) >= len) {
      break;
    }
  }
  return geom::GeoFactory::createMultiLineString(
      std::move(lines), getGeoReference());
}

geom::GeoMultiPolygon::Ptr
WKTReader::readMultiPolygon(std::string_view wkt) {
  std::vector<geom::GeoPolygon::Ptr> ps;

  int i = 1, len = wkt.size();
  while (int n = findNextToken(wkt.substr(i), "))") + 1) {
    ps.push_back(readPolygon(wkt.substr(i, n)));
    if ((i += n + 3) >= len) {
      break;
    }
  }
  return geom::GeoFactory::createMultiPolygon(std::move(ps), getGeoReference());
}

geom::GeoCoordinate
WKTReader::readCoordinate(std::string_view wkt) {
  double lon, lat;
  std::sscanf(wkt.data(), "%lf %lf", &lon, &lat);
  return geom::GeoFactory::createCoordinate(lon, lat, getGeoReference());
}

geom::GeoCoordinateSequence::Ptr
WKTReader::readCoordinateSequence(std::string_view wkt) {
  std::vector<size_t> pos = {0};
  for (std::size_t i = 0; i != wkt.size(); ++i) {
    if (wkt.at(i) == ',') {
      pos.push_back(i + 1);
    }
  }
  pos.push_back(wkt.size());

  std::vector<geom::GeoCoordinate> coords(pos.size() - 1);
  for (std::size_t i = 0; i != pos.size() - 1; ++i) {
    coords[i] = readCoordinate(wkt.substr(pos[i], pos[i + 1] - pos[i] - 1));
  }
  return geom::GeoFactory::createCoordinateSequence(
      std::move(coords), getGeoReference());
}

int
WKTReader::findNextToken(std::string_view str, char token) {
  return str.find_first_of(token);
}

int
WKTReader::findNextToken(std::string_view str, std::string_view token) {
  std::size_t n = str.size(), m = token.size();
  if (n < m) {
    return -1;
  }
  for (std::size_t i = 0; i != n - m + 1; ++i) {
    if (str.substr(i, m) == token) {
      return i;
    }
  }
  return -1;
}

} // namespace io
} // namespace ep