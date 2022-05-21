#ifndef ELLIPSOID_ALGORITHM_METRIC_GAUSSSECONDTHEME_H_
#define ELLIPSOID_ALGORITHM_METRIC_GAUSSSECONDTHEME_H_

#include <algorithm/metric/SecondTheme.h>
#include <geom/GeoEarth.h>

namespace ep {
namespace alg {

class GaussSecondTheme : public SecondTheme {
public:
  GaussSecondTheme(
      const geom::GeoEarth &earth = geom::GeoEarth::GeoEarth_WGS84);

  ~GaussSecondTheme() override = default;

  double evaluateDistance(const geom::GeoCoordinate *coord1,
                          const geom::GeoCoordinate *coord2, double &a1,
                          double &a2) override;

  double evaluateDistance(const geom::GeoCoordinate *coord1,
                          const geom::GeoCoordinate *coord2) override;
};

} // namespace alg
} // namespace ep

#endif // ELLIPSOID_ALGORITHM_METRIC_GAUSSSECONDTHEME_H_