#ifndef ELLIPSOID_GEOM_MULTILINESTRING_H_
#define ELLIPSOID_GEOM_MULTILINESTRING_H_

#include "geom/GeoGeometry.h"
#include "geom/GeoLineString.h"
#include "geom/GeoReferenceSystem.h"

#include <memory>
#include <vector>

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

  GeoLineString       *getLineString(std::size_t index);
  const GeoLineString *getLineString(std::size_t index) const;

  std::unique_ptr<GeoLineString> getLineStringNew(std::size_t index) const;

#ifdef EP_OPENGL
  void draw() const override;
#endif

protected:
  GeoMultiLineString(std::vector<std::unique_ptr<GeoLineString>> &&lines,
      GeoReferenceSystem                                           ref);

private:
  std::vector<std::unique_ptr<GeoLineString>> lines_;
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_MULTILINESTRING_H_