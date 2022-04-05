#ifndef ELLIPSOID_IO_WKTREADER_H_
#define ELLIPSOID_IO_WKTREADER_H_

#include <geom/GeoGeometry.h>
#include <geom/GeoFactory.h>
#include <string>
#include <memory>

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
}
}

namespace ep {
namespace io {

class WKTReader
{
public:
    WKTReader() = default;
    
    ~WKTReader() = default;

    geom::GeoGeometry::Ptr read(const std::string &wkt);

    // template<typename T>
    // std::unique_ptr<T> read(const std::string &wkt) {
    //     if (auto p = dynamic_cast<T *>(read(wkt).get())) {
    //         return std::unique_ptr<T>(p);
    //     }
    // }

private:
    // WKT form: x y
    geom::GeoCoordinate readCoordinate(const std::string &wkt);

    // WKT form: x1 y1,...,xn yn
    std::unique_ptr<geom::GeoCoordinateSequence> readCoordinateSequence(const std::string &wkt);

    // WKT form: x y
    std::unique_ptr<geom::GeoPoint> readPoint(const std::string &wkt);
    
    // WKT form: x1 y1,x2 y2
    std::unique_ptr<geom::GeoLineSegment> readLineSegment(const std::string &wkt);
    
    // WKT form: x1 y1,...,xn yn
    std::unique_ptr<geom::GeoLineString> readLineString(const std::string &wkt);
    
    // WKT form: x1 y1,...,xn yn,x1 y1
    std::unique_ptr<geom::GeoLinearRing> readLinearRing(const std::string &wkt);
    
    // WKT form:
    //  (x01 y01,...,x0n y0n,x01 y01),
    //  (x11 y11,...,x1n y1n,x11 y11),
    //  ...,
    //  (xm1 ym1,...,xmn ymn,xm1 ym1)
    std::unique_ptr<geom::GeoPolygon> readPolygon(const std::string &wkt);
    
    // WKT form:
    //  (x11 y11,...,x1n y1n),
    //  ...,
    //  (xm1 ym1,...,xmn ymn)
    std::unique_ptr<geom::GeoMultiLineString> readMultiLineString(const std::string &wkt);
    
    // WKT form:
    //  ((x011 y011,...,x0n1 y0n1,x011 y011)
    //   ...,
    //   (xm11 ym11,...,xmn1 ymn1,xm11 ym11)),
    //  ...,
    //  ((x01k y01k,...,x0nk y0nk,x01k y01k)
    //   ...,
    //   (xm1k ym1k,...,xmnk ymnk,xm1k ym1k)))
    std::unique_ptr<geom::GeoMultiPolygon> readMultiPolygon(const std::string &wkt);

    // return the index of first occurrence in `str` that equals the given token, -1 if not found
    int findNextToken(const std::string &str, char token);

    // return the index of first occurrence of starting position, -1 if not found
    int findNextToken(const std::string &str, const std::string &token);

private:
    geom::GeoFactory gf;
};



} // namespace io
} // namespace ep

#endif