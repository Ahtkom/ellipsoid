#ifndef ELLIPSOID_OP_EARTHLOADER_H_
#define ELLIPSOID_OP_EARTHLOADER_H_

#include <geom/GeoEarth.h>

namespace ep {
namespace op {
    
class GeoEarthLoader
{
public:
    GeoEarthLoader(const geom::GeoEarth &earth);
    
    virtual ~GeoEarthLoader() = default;

    geom::GeoEarth getGeoEarth() const;

    void setGeoEarth(const geom::GeoEarth &earth);

    void initGeoEarthConstants();

protected:
    geom::GeoEarth earth_;
    double a;  // 
    double b;  // 
    double c;  // 
    double e1; // 
    double e2; // 
};


} // namespace op
} // namespace ep


#endif