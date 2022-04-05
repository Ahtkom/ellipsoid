#ifndef ELLIPSOID_OP_METRIC_BASEMETRIC_H_
#define ELLIPSOID_OP_METRIC_BASEMETRIC_H_

#include <geom/GeoEarth.h>
#include <op/GeoEarthLoader.h>

namespace ep {
namespace op {

class BaseMetric : public GeoEarthLoader
{
public:
    BaseMetric(const geom::GeoEarth &earth)
        : GeoEarthLoader(earth)
    {}
    
    ~BaseMetric() override = default;
};


} // namespace op
} // namespace ep

#endif