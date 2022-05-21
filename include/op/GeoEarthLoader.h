#ifndef ELLIPSOID_OP_EARTHLOADER_H_
#define ELLIPSOID_OP_EARTHLOADER_H_

#include <geom/GeoEarth.h>

namespace ep {
namespace op {

/**
 * @brief Provide direct access to ellipsoid constants through inheritance and
 *        will not help runtime performance.
 */
class GeoEarthLoader {
public:
  GeoEarthLoader(const geom::GeoEarth &earth);

  virtual ~GeoEarthLoader() = default;

  geom::GeoEarth getGeoEarth() const;

  void setGeoEarth(const geom::GeoEarth &earth);

  void initGeoEarthConstants();

protected:
  double a; //

  double b; //

  double c; //

  double e1; //

  double e2; //

private:
  geom::GeoEarth earth_;
};

} // namespace op
} // namespace ep

#endif // ELLIPSOID_OP_EARTHLOADER_H_