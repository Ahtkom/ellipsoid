#include <geom/GeoGeometry.h>
#include <io/GeoJsonWriter.h>
#include <io/WKTWriter.h>

namespace ep {
namespace geom {
    
std::string GeoGeometry::toGeoJson() const
{
    io::GeoJsonWriter writer;
    return writer.write(this);
}

std::string GeoGeometry::toWKT() const
{
    io::WKTWriter writer;
    return writer.write(this);
}

} // namespace geom
} // namespace ep   