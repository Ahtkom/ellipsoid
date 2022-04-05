#ifndef ELLIPSOID_IO_WKTWRITER_H_
#define ELLIPSOID_IO_WKTWRITER_H_

#include <geom/GeoGeometry.h>
#include <string>

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

class WKTWriter
{
public:
    WKTWriter() = default;

    ~WKTWriter() = default;

    std::string write(const geom::GeoGeometry *geometry);

private:
    std::string writePoint(const geom::GeoPoint *pt);

    std::string writeLineSegment(const geom::GeoLineSegment *seg);

    std::string writeLineString(const geom::GeoLineString *ls);

    std::string writeLinearRing(const geom::GeoLinearRing *lr);

    std::string writePolygon(const geom::GeoPolygon *p);

    std::string writeMultiLineString(const geom::GeoMultiLineString *mls);
    
    std::string writeMultiPolygon(const geom::GeoMultiPolygon *mp);

    std::string writeCoordinate(const geom::GeoCoordinate *c);

    std::string writeCoordinateSequence(const geom::GeoCoordinateSequence *cseq);
};
    

} // namespace io
} // namespace ep


#endif