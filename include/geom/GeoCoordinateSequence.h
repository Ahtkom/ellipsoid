#ifndef ELLIPSOID_GEOM_GEOCOORDINATESEQUENCE_H_
#define ELLIPSOID_GEOM_GEOCOORDINATESEQUENCE_H_

#include <geom/GeoCoordinate.h>

#include <memory>
#include <vector>

namespace ep {
namespace geom {

class GeoCoordinateSequence {
  friend class GeoFactory;

public:
  using Ptr = std::unique_ptr<GeoCoordinateSequence>;

  GeoCoordinateSequence(std::vector<GeoCoordinate> &&coords);

  ~GeoCoordinateSequence() = default;

  TO_STRING_METHOD_WITH_OSTREAM(GeoCoordinateSequence)

  std::size_t getNumCoordinate() const;

  GeoCoordinate *getCoordinate(std::size_t index);

  const GeoCoordinate *getCoordinate(std::size_t index) const;

#ifdef EP_OPENGL
  void draw() const;
#endif

private:
  std::vector<GeoCoordinate> coords_;
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_GEOCOORDINATESEQUENCE_H_