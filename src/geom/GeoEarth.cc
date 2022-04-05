#include <geom/GeoEarth.h>

namespace ep {
namespace geom {

const GeoEarth GeoEarth::GeoEarth_WGS84{6378137.0, 298.257223563};
const GeoEarth GeoEarth::GeoEarth_Krasovsky{6378245.0, 298.3};
const GeoEarth GeoEarth::GeoEarth_GRS80{6378137.0, 298.257222101};
const GeoEarth GeoEarth::GeoEarth_China80{6378140.0, 298.257};

} // namespace geom
} // namespace ep