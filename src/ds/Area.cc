#include "ds/Area.h"

constexpr long double sqm_per_sqkm = 1000000.0L;
constexpr long double sqm_per_ha   = 10000.0L;
constexpr long double sqm_per_acre = 666.666667L;

namespace ep {
namespace ds {

Area::Area(long double v)
    : square_meters_(v) { }

Area::operator long double() const { return getSquareMeters(); }

long double
Area::getSquareMeters() const {
  return square_meters_;
}

long double
Area::getSquareKilometers() const {
  return getSquareMeters() / sqm_per_sqkm;
}

long double
Area::getHectares() const {
  return getSquareMeters() / sqm_per_ha;
}

long double
Area::getAcres() const {
  return getSquareMeters() / sqm_per_acre;
}

} // namespace ds
} // namespace ep

ep::ds::Area operator"" _sqm(long double v) { return v; }

ep::ds::Area operator"" _sqkm(long double v) { return v * sqm_per_sqkm; }

ep::ds::Area operator"" _ha(long double v) { return v * sqm_per_ha; }

ep::ds::Area operator"" _acre(long double v) { return v * sqm_per_acre; }
