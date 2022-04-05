#ifndef ELLIPSOID_GEOM_GEOGEOMETRY_H_
#define ELLIPSOID_GEOM_GEOGEOMETRY_H_

#include <memory>
#include <vector>
#include <string>

namespace ep {
namespace geom {
    
class GeoGeometry
{
public:
    using Ptr = std::unique_ptr<GeoGeometry>;

    using ConstVect = std::vector<const GeoGeometry *>;

    virtual ~GeoGeometry() = default;

    // Output geometry object in GeoJson format.
    std::string toGeoJson() const;
    
    // Output geometry object in WKT format.
    std::string toWKT() const;

    virtual std::string getGeometryType() const = 0;

    // TODO: implement
    virtual bool isSimple() const {
        return true;
    }
};

} // namespace geom
} // namespace ep   


#endif