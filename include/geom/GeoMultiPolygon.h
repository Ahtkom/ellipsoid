#ifndef ELLIPSOID_GEOM_MULTIPOLYGON_H_
#define ELLIPSOID_GEOM_MULTIPOLYGON_H_

#include <geom/GeoGeometry.h>
#include <geom/GeoPolygon.h>

#include <memory>
#include <vector>

namespace ep {
namespace geom {

class GeoMultiPolygon : public GeoGeometry {
  friend class GeoFactory;

public:
  using Ptr = std::unique_ptr<GeoMultiPolygon>;

  ~GeoMultiPolygon() override = default;

  std::string getGeometryType() const override;

  std::size_t getNumPolygon() const;

  GeoPolygon *getPolygonN(std::size_t index);

  const GeoPolygon *getPolygonN(std::size_t index) const;

#ifdef EP_OPENGL
  void draw() const override;
#endif

protected:
  GeoMultiPolygon(std::vector<std::unique_ptr<GeoPolygon>> &&ps);

private:
  std::vector<std::unique_ptr<GeoPolygon>> ps_;
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_MULTIPOLYGON_H_