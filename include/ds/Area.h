#ifndef ELLIPSOID_DS_AREA_H_
#define ELLIPSOID_DS_AREA_H_

namespace ep {
namespace ds {

class Area
{
  using value_type = long double;

public:
  Area(value_type v);

  operator value_type() const;

  value_type getSquareMeters() const;
  value_type getSquareKilometers() const;
  value_type getHectares() const;
  value_type getAcres() const;

private:
  value_type square_meters_;
};

} // namespace ds
} // namespace ep

ep::ds::Area operator"" _sqm(long double v);
ep::ds::Area operator"" _sqkm(long double v);
ep::ds::Area operator"" _ha(long double v);
ep::ds::Area operator"" _acre(long double v);

#endif // ELLIPSOID_DS_AREA_H_