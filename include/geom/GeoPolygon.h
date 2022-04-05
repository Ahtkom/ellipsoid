#ifndef ELLIPSOID_GEOM_GEOPOLYGON_H_
#define ELLIPSOID_GEOM_GEOPOLYGON_H_

#include <geom/GeoGeometry.h>
#include <geom/GeoLinearRing.h>
#include <memory>
#include <vector>

namespace ep {
namespace geom {

class GeoPolygon : public GeoGeometry
{
    friend class GeoFactory;

public:
    using Ptr = std::unique_ptr<GeoPolygon>;

    ~GeoPolygon() override = default;

    std::string getGeometryType() const override;

    std::size_t getNumInteriorRing() const;

    GeoLinearRing *getExteriorRing();

    const GeoLinearRing *getExteriorRing() const;

    GeoLinearRing *getInteriorRingN(std::size_t index);

    const GeoLinearRing *getInteriorRingN(std::size_t index) const;

protected:
    GeoPolygon(GeoLinearRing::Ptr &&shell);

    GeoPolygon(GeoLinearRing::Ptr &&shell, std::vector<GeoLinearRing::Ptr> &&holes);

private:
    GeoLinearRing::Ptr shell_;

    std::vector<GeoLinearRing::Ptr> holes_;
};


} // namespace geom
} // namespace ep

#endif