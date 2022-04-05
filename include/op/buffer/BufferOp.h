#ifndef ELLIPSOID_OP_BUFFER_BUFFEROP_H_
#define ELLIPSOID_OP_BUFFER_BUFFEROP_H_

#include <geom/GeoGeometry.h>

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
namespace op {

class BufferOp
{
public:
    BufferOp() = default;

    ~BufferOp() = default;

    geom::GeoGeometry::Ptr buffer(const geom::GeoGeometry *geometry, double dist);

private:
    geom::GeoPolygon::Ptr bufferOfPoint(const geom::GeoPoint *pt, double dist);
   
    geom::GeoPolygon::Ptr bufferOfLineSegment(const geom::GeoLineSegment *seg, double dist);
    
    geom::GeoPolygon::Ptr bufferOfLineString(const geom::GeoLineString *ls, double dist);

    geom::GeoPolygon::Ptr bufferOfLinearRing(const geom::GeoLinearRing *lr, double dist);

    geom::GeoPolygon::Ptr bufferOfPolygon(const geom::GeoPolygon *p, double dist);

    geom::GeoCoordinateSequence::Ptr bufferOfCoordinate(const geom::GeoCoordinate *c, double dist);

    geom::GeoPolygon::Ptr bufferOfCoordinateSequence(const geom::GeoCoordinateSequence *cseq, double dist);
};


} // namespace op
} // namespace ep


#endif