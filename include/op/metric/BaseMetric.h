#ifndef ELLIPSOID_OP_METRIC_BASEMETRIC_H_
#define ELLIPSOID_OP_METRIC_BASEMETRIC_H_

#include <geom/GeoEarth.h>

namespace ep {
namespace op {

/**
 * @brief Base class for metric classes, only used for inheritance.
 */
class BaseMetric {
public:
  BaseMetric(const geom::GeoEarth &earth) : earth_(earth) {}

  virtual ~BaseMetric() = default;

  geom::GeoEarth getGeoEarth() const { return earth_; }

  virtual void setGeoEarth(const geom::GeoEarth &earth) { earth_ = earth; }

private:
  geom::GeoEarth earth_;
};

} // namespace op
} // namespace ep

#endif // ELLIPSOID_OP_METRIC_BASEMETRIC_H_