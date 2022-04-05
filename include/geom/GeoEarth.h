#ifndef ELLIPSOID_GEOM_GEOEARTH_H_
#define ELLIPSOID_GEOM_GEOEARTH_H_

#include <util/Macro.h>
#include <string>

namespace ep {
namespace geom {

class GeoEarth
{
public:
    static const GeoEarth GeoEarth_WGS84;
    static const GeoEarth GeoEarth_Krasovsky;
    static const GeoEarth GeoEarth_GRS80;
    static const GeoEarth GeoEarth_China80;

    GeoEarth(double a, double alpha)
        : a_(a)
        , alpha_(alpha)
    {}

    ~GeoEarth() = default;

    double getA() const { return a_; }
    double getAlpha() const { return alpha_; }
    void setA(double a) { a_ = a; }
    void setAlpha(double alpha) { alpha_ = alpha; }

private:
    double a_;
    double alpha_;
};


} // namespace geom
} // namespace ep

#endif