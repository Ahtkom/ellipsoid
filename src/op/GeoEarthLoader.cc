#include <op/GeoEarthLoader.h>
#include <math.h>

namespace ep {
namespace op {
    
GeoEarthLoader::GeoEarthLoader(const geom::GeoEarth &earth)
    : earth_(earth)
{
    initGeoEarthConstants();
}

geom::GeoEarth GeoEarthLoader::getGeoEarth() const
{
    return earth_;
}

void GeoEarthLoader::setGeoEarth(const geom::GeoEarth &earth)
{
    earth_ = earth;
    initGeoEarthConstants();
}

void GeoEarthLoader::initGeoEarthConstants()
{
    a = earth_.getA();
    b = a - (a / earth_.getAlpha());
    c = a * a / b;
    e1 = 1 - pow(b / a, 2);
    e2 = pow(a / b, 2) - 1;
}


} // namespace op
} // namespace ep