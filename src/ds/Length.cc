#include "ds/Length.h"

constexpr long double m_per_km   = 1000.0L;
constexpr long double m_per_mile = 1609.344L;

namespace ep {
namespace ds {

Length::Length(long double v)
    : meters_(v) { }

Length::operator long double() const { return getMeters(); }

long double
Length::getKilometers() const {
  return getMeters() / m_per_km;
}

long double
Length::getMeters() const {
  return meters_;
}

long double
Length::getMiles() const {
  return getMeters() / m_per_mile;
}

} // namespace ds
} // namespace ep

ep::ds::Length operator"" _m(long double v) { return v; }

ep::ds::Length operator"" _km(long double v) { return v * m_per_km; }

ep::ds::Length operator"" _mi(long double v) { return v * m_per_mile; }