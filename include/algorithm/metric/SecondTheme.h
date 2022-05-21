#ifndef ELLIPSOID_ALGORITHM_METRIC_SECONDTHEME_H_
#define ELLIPSOID_ALGORITHM_METRIC_SECONDTHEME_H_

#include <geom/GeoCoordinate.h>
#include <geom/GeoEarth.h>
#include <op/GeoEarthLoader.h>

namespace ep {
namespace alg {

/**
 * @brief Base class for all \b second-theme algorithms.
 *
 */
class SecondTheme : public op::GeoEarthLoader {
public:
  SecondTheme(const geom::GeoEarth &earth = geom::GeoEarth::GeoEarth_WGS84)
      : op::GeoEarthLoader(earth) {}

  ~SecondTheme() override = default;

  /**
   * @brief
   *
   * @param coord1
   * @param coord2
   * @param a1
   * @param a2
   * @return double
   */
  virtual double evaluateDistance(const geom::GeoCoordinate *coord1,
                                  const geom::GeoCoordinate *coord2, double &a1,
                                  double &a2) = 0;

  // without azimuth angles
  virtual double evaluateDistance(const geom::GeoCoordinate *coord1,
                                  const geom::GeoCoordinate *coord2) = 0;
};

} // namespace alg
} // namespace ep

#endif // ELLIPSOID_ALGORITHM_METRIC_SECONDTHEME_H_