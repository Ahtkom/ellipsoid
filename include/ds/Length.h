#ifndef ELLIPSOID_DS_LENGTH_H_
#define ELLIPSOID_DS_LENGTH_H_

namespace ep {
namespace ds {

class Length
{
  using value_type = long double;

public:
  Length(value_type v);

  operator value_type() const;

  value_type getMeters() const;
  value_type getKilometers() const;
  value_type getMiles() const;

private:
  value_type meters_ = 0.0;
};

} // namespace ds
} // namespace ep

ep::ds::Length operator"" _m(long double v);
ep::ds::Length operator"" _km(long double v);
ep::ds::Length operator"" _mi(long double v);

#endif // ELLIPSOID_DS_LENGTH_H_