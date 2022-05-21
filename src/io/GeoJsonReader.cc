#include <io/GeoJsonReader.h>
#include <io/ParseException.h>
#include <geom/GeoCoordinate.h>
#include <geom/GeoCoordinateSequence.h>
#include <geom/GeoPoint.h>
#include <geom/GeoLineSegment.h>
#include <geom/GeoLineString.h>
#include <geom/GeoLinearRing.h>
#include <geom/GeoPolygon.h>
#include <geom/GeoMultiLineString.h>
#include <geom/GeoMultiPolygon.h>

#include <iostream>

namespace ep {
namespace io {

geom::GeoGeometry::Ptr
GeoJsonReader::read(const std::string &geojson_str)
{
    return read(nlohmann::json::parse(geojson_str));
}

geom::GeoGeometry::Ptr
GeoJsonReader::read(const nlohmann::json &geojson)
{
    // TODO other specifiers
    if (geojson.contains("type")) {
        if (geojson["type"] == "Feature") {
            return readGeometryCoordinates(geojson["geometry"]);
        } else if (geojson["type"] == "FeatureCollection") {
            throw ParseException(__PRETTY_FUNCTION__,
                ": FeatureCollection not supported!");
        } else {
            if (geojson.contains("coordinates")) {
                return readGeometryCoordinates(geojson);
            } else {
                    throw ParseException(__PRETTY_FUNCTION__,
        "Invalid GeoJson data <no type specifier>: " + geojson.dump());
            }
        }        
    }

    throw ParseException(__PRETTY_FUNCTION__,
        "Invalid GeoJson data <no type specifier>: " + geojson.dump());
}

geom::GeoGeometry::Ptr
GeoJsonReader::readGeometryCoordinates(const nlohmann::json &geojson)
{
    if (geojson.contains("type") && geojson.contains("coordinates")) {
        const nlohmann::json &coordinates = geojson["coordinates"];
        std::string geometryType = geojson["type"];

        if (geometryType == "Point") {
            return readPoint(coordinates);
        } else if (geometryType == "LineSegment") {
            return readLineSegment(coordinates);
        } else if (geometryType == "LineString") {
            return readLineString(coordinates);
        } else if (geometryType == "LinearRing") {
            return readLinearRing(coordinates);
        } else if (geometryType == "Polygon") {
            return readPolygon(coordinates);
        } else if (geometryType == "MultiLineString") {
            return readMultiLineString(coordinates);
        } else if (geometryType == "MultiPolygon") {
            return readMultiPolygon(coordinates);
        } else {
            throw ParseException(__PRETTY_FUNCTION__,
                "Geometry type " + geometryType + " not supported!");
        }
    }

    throw ParseException(__PRETTY_FUNCTION__,
        "Invalid GeoJson data <no type or coordinates specifier>: " +
        geojson.dump());
}

geom::GeoCoordinate
GeoJsonReader::readCoordinate(const nlohmann::json &geojson)
{
    if (geojson.is_array() && geojson.size() == 2) {
        return {geojson[0], geojson[1]};
    }

    throw ParseException(__PRETTY_FUNCTION__,
        "Invalid GeoJson data for coordinate: " + geojson.dump());
}

geom::GeoCoordinateSequence::Ptr
GeoJsonReader::readCoordinateSequence(const nlohmann::json &geojson)
{
    if (geojson.is_array()) {
        std::vector<geom::GeoCoordinate> coords;
        std::size_t n = geojson.size();
        coords.reserve(n);

        for (std::size_t i = 0; i != n; ++i) {
            coords.push_back(readCoordinate(geojson[i]));
        }

        return gf.createCoordinateSequence(std::move(coords));
    }
    
    throw ParseException(__PRETTY_FUNCTION__,
        "Invalid GeoJson data for coordinate sequence: " + geojson.dump());
}

geom::GeoPoint::Ptr
GeoJsonReader::readPoint(const nlohmann::json &geojson)
{
    return gf.createPoint(readCoordinate(geojson));
}
    
geom::GeoLineSegment::Ptr
GeoJsonReader::readLineSegment(const nlohmann::json &geojson)
{
    return gf.createLineSegment(readCoordinateSequence(geojson));
}
    
geom::GeoLineString::Ptr
GeoJsonReader::readLineString(const nlohmann::json &geojson)
{
    return gf.createLineString(readCoordinateSequence(geojson));
}
    
geom::GeoLinearRing::Ptr
GeoJsonReader::readLinearRing(const nlohmann::json &geojson)
{
    return gf.createLinearRing(readCoordinateSequence(geojson));
}

geom::GeoPolygon::Ptr
GeoJsonReader::readPolygon(const nlohmann::json &geojson)
{
    if (geojson.is_array()) {
        std::vector<geom::GeoLinearRing::Ptr> rings;
        std::size_t n = geojson.size();
        rings.reserve(n);

        for (std::size_t i = 0; i != n; ++i) {
            rings.push_back(readLinearRing(geojson[i]));
        }

        return gf.createPolygon(std::move(rings));
    }

    throw ParseException(__PRETTY_FUNCTION__,
        "Invalid GeoJson data for Polygon: " + geojson.dump());
}
    
geom::GeoMultiLineString::Ptr
GeoJsonReader::readMultiLineString(const nlohmann::json &geojson)
{
    if (geojson.is_array()) {
        std::vector<geom::GeoLineString::Ptr> lines;
        std::size_t n = geojson.size();
        lines.reserve(n);

        for (std::size_t i = 0; i != n; ++i) {
            lines.push_back(readLineString(geojson[i]));
        }

        return gf.createMultiLineString(std::move(lines));
    }

    throw ParseException(__PRETTY_FUNCTION__,
        "Invalid GeoJson data for MultiLineString: " + geojson.dump());
}

geom::GeoMultiPolygon::Ptr
GeoJsonReader::readMultiPolygon(const nlohmann::json &geojson)
{
    if (geojson.is_array()) {
        std::vector<geom::GeoPolygon::Ptr> ps;
        std::size_t n = geojson.size();
        ps.reserve(n);

        for (std::size_t i = 0; i != n; ++i) {
            ps.push_back(readPolygon(geojson[i]));
        }

        return gf.createMultiPolygon(std::move(ps));
    }

    throw ParseException(__PRETTY_FUNCTION__,
        "Invalid GeoJson data for MultiPolygon: " + geojson.dump());
}


} // namespace io
} // namespace ep