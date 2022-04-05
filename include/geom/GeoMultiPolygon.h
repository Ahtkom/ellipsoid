#ifndef ELLIPSOID_GEOM_MULTIPOLYGON_H_
#define ELLIPSOID_GEOM_MULTIPOLYGON_H_

#include <geom/GeoGeometry.h>
#include <geom/GeoPolygon.h>
#include <vector>
#include <memory>

namespace ep {
namespace geom {

class GeoMultiPolygon : public GeoGeometry
{
    friend class GeoFactory;

public:
    using Ptr = std::unique_ptr<GeoMultiPolygon>;

    ~GeoMultiPolygon() override = default;

    std::string getGeometryType() const override;

    std::size_t getNumPolygon() const;

    GeoPolygon *getPolygonN(std::size_t index);

    const GeoPolygon *getPolygonN(std::size_t index) const;

protected:
    GeoMultiPolygon(std::vector<GeoPolygon::Ptr> &&ps);

private:
    std::vector<GeoPolygon::Ptr> ps_;
};


} // namespace geom
} // namespace ep

#endif