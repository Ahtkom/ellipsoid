#ifndef ELLIPSOID_ALGORITHM_METRIC_FIRSTTHEME_H_
#define ELLIPSOID_ALGORITHM_METRIC_FIRSTTHEME_H_

#include <geom/GeoCoordinate.h>
#include <geom/GeoEarth.h>
#include <op/GeoEarthLoader.h>

namespace ep {
namespace alg {

/**
 * @brief Base class for all \b first-theme algorithms.
 *
 */
class FirstTheme : public op::GeoEarthLoader {
public:
  FirstTheme(const geom::GeoEarth &earth = geom::GeoEarth::GeoEarth_WGS84)
      : op::GeoEarthLoader(earth) {}

  ~FirstTheme() override = default;

  /**
   * @brief
   *
   * @param coord
   * @param dist
   * @param a1
   * @param a2
   * @return geom::GeoCoordinate
   */
  virtual geom::GeoCoordinate getTargetCoord(const geom::GeoCoordinate *coord,
                                             double dist, double a1,
                                             double &a2) = 0;

  // without second azimuth angle
  virtual geom::GeoCoordinate getTargetCoord(const geom::GeoCoordinate *coord,
                                             double dist, double a1) = 0;
};

} // namespace alg
} // namespace ep

#endif // ELLIPSOID_ALGORITHM_METRIC_FIRSTTHEME_H_