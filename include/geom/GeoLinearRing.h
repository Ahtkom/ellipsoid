#ifndef ELLIPSOID_GEOM_GEOLINEARRING_H_
#define ELLIPSOID_GEOM_GEOLINEARRING_H_

#include <geom/GeoLineString.h>

#include <memory>

namespace ep {
namespace geom {

class GeoLinearRing : public GeoLineString {
  friend class GeoFactory;

public:
  using Ptr = std::unique_ptr<GeoLinearRing>;

  ~GeoLinearRing() override = default;

  std::string getGeometryType() const override;

  bool isClosed() const override;

protected:
  GeoLinearRing(GeoCoordinateSequence::Ptr &&pts);

private:
  bool validate() const;
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_GEOLINEARRING_H_