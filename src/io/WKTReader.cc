#include <io/WKTReader.h>
#include <util/IllegalArgumentException.h>
#include <geom/GeoCoordinate.h>
#include <geom/GeoCoordinateSequence.h>
#include <geom/GeoPoint.h>
#include <geom/GeoLineSegment.h>
#include <geom/GeoLineString.h>
#include <geom/GeoLinearRing.h>
#include <geom/GeoPolygon.h>
#include <geom/GeoMultiLineString.h>
#include <geom/GeoMultiPolygon.h>

namespace ep {
namespace io {

geom::GeoGeometry::Ptr WKTReader::read(const std::string &wkt)
{
    std::size_t n = wkt.size();
    if (n >= 10) {
        if (wkt.substr(0, 5) == "POINT") {
            return readPoint(wkt.substr(6));
        } else if (wkt.substr(0, 11) == "LINESEGMENT") {
            return readLineSegment(wkt.substr(12, n - 13));
        } else if (wkt.substr(0, 10) == "LINESTRING") {
            return readLineString(wkt.substr(11, n - 12));
        } else if (wkt.substr(0, 10) == "LINEARRING") {
            return readLinearRing(wkt.substr(11, n - 12));
        } else if (wkt.substr(0, 7) == "POLYGON") {
            return readPolygon(wkt.substr(8, n - 9));
        } else if (wkt.substr(0, 15) == "MULTILINESTRING") {
            return readMultiLineString(wkt.substr(16, n - 17));
        } else if (wkt.substr(0, 12) == "MULTIPOLYGON") {
            return readMultiPolygon(wkt.substr(13, n - 14));
        }
    }
    throw util::IllegalArgumentException("Invalid WKT form!");
}

geom::GeoPoint::Ptr WKTReader::readPoint(const std::string &wkt)
{
    return gf.createGeoPoint(readCoordinate(wkt));
}

geom::GeoLineSegment::Ptr WKTReader::readLineSegment(const std::string &wkt)
{
    return gf.createGeoLineSegment(readCoordinateSequence(wkt));
}

geom::GeoLineString::Ptr WKTReader::readLineString(const std::string &wkt)
{
    return gf.createGeoLineString(readCoordinateSequence(wkt));
}

geom::GeoLinearRing::Ptr WKTReader::readLinearRing(const std::string &wkt)
{
    return gf.createGeoLinearRing(readCoordinateSequence(wkt));
}

geom::GeoPolygon::Ptr WKTReader::readPolygon(const std::string &wkt)
{
    std::vector<geom::GeoLinearRing::Ptr> rings;
    int i = 1, len = wkt.size();
    while (int n = findNextToken(wkt.substr(i), ')') + 1) {
        rings.push_back(readLinearRing(wkt.substr(i, n - 1)));
        if ((i += n + 2) >= len) {
            break;
        }
    }
    return gf.createGeoPolygon(std::move(rings));
}

geom::GeoMultiLineString::Ptr WKTReader::readMultiLineString(const std::string &wkt)
{
    std::vector<geom::GeoLineString::Ptr> lines;
    int i = 1, len = wkt.size();
    while (int n = findNextToken(wkt.substr(i), ')') + 1) {
        lines.push_back(readLineString(wkt.substr(i, n - 1)));
        if ((i += n + 2) >= len) {
            break;
        }
    }
    return gf.createGeoMultiLineString(std::move(lines));
}

geom::GeoMultiPolygon::Ptr WKTReader::readMultiPolygon(const std::string &wkt)
{
    std::vector<geom::GeoPolygon::Ptr> ps;
    int i = 1, len = wkt.size();
    while (int n = findNextToken(wkt.substr(i), "))") + 1) {
        ps.push_back(readPolygon(wkt.substr(i, n)));
        if ((i += n + 3) >= len) {
            break;
        }
    }
    return gf.createGeoMultiPolygon(std::move(ps));
}

geom::GeoCoordinate WKTReader::readCoordinate(const std::string &wkt)
{
    int i = findNextToken(wkt, ' ');
    if (i != -1) {
        return gf.createGeoCoordinate(
            std::stod(wkt.substr(0, i)),
            std::stod(wkt.substr(i + 1)));
    }
    // if (index != -1) {
        // int index2 = findNextToken(wkt.substr(index + 1), ' ');
        // if (index2 != -1) {
            // return gf.createGeoCoordinate(
                // std::stod(wkt.substr(0, index)),
                // std::stod(wkt.substr(index + 1, index2)),
                // std::stod(wkt.substr(index + index2 + 2)));
        // }
    // }
    throw util::IllegalArgumentException("Invalid WKT form!");
}

geom::GeoCoordinateSequence::Ptr WKTReader::readCoordinateSequence(const std::string &wkt)
{
    std::vector<geom::GeoCoordinate> coords;
    int i = 0;
    while (int n = findNextToken(wkt.substr(i), ',') + 1) {
        coords.push_back(readCoordinate(wkt.substr(i, n - 1)));
        i += n;
    }
    coords.push_back(readCoordinate(wkt.substr(i)));
    return gf.createGeoCoordinateSequence(std::move(coords));
}

int WKTReader::findNextToken(const std::string &str, char token)
{
    return str.find_first_of(token);
}

int WKTReader::findNextToken(const std::string &str, const std::string &token)
{
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