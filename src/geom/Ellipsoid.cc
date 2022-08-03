#include "geom/Ellipsoid.h"

namespace ep {
namespace geom {

const Ellipsoid Ellipsoid::Undefined       = {0.0, 0.0};
const Ellipsoid Ellipsoid::CGCS_2000       = {6378137, 298.257222101};
const Ellipsoid Ellipsoid::Bessel_1841     = {6377397.155, 299.1528128};
const Ellipsoid Ellipsoid::Clarke_1866     = {6378206.4, 294.978698213898};
const Ellipsoid Ellipsoid::GRS_1980        = {6378137, 298.257222101};
const Ellipsoid Ellipsoid::Krassowsky_1940 = {6378245, 298.3};
const Ellipsoid Ellipsoid::WGS_84          = {6378137, 298.257223563};

} // namespace geom
} // namespace ep