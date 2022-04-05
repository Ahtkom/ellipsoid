#ifndef ELLIPSOID_GEOM_MULTILINESTRING_H_
#define ELLIPSOID_GEOM_MULTILINESTRING_H_

#include <geom/GeoGeometry.h>
#include <geom/GeoLineString.h>
#include <vector>
#include <memory>

namespace ep {
namespace geom {

class GeoMultiLineString : public GeoGeometry
{
    friend class GeoFactory;

public:
    using Ptr = std::unique_ptr<GeoMultiLineString>;
    
    ~GeoMultiLineString() override = default;

    std::string getGeometryType() const override;

    std::size_t getNumLineString() const;

    GeoLineString *getLineStringN(std::size_t index);

    const GeoLineString *getLineStringN(std::size_t index) const;

protected:
    GeoMultiLineString(std::vector<GeoLineString::Ptr> &&lines);

private:
    std::vector<GeoLineString::Ptr> lines_;
};



} // namespace geom
} // namespace ep

#endif