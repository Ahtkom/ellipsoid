#ifndef ELLIPSOID_GEOM_GEOLINESTRING_H_
#define ELLIPSOID_GEOM_GEOLINESTRING_H_

#include "geom/GeoCoordinateSequence.h"
#include "geom/GeoGeometry.h"
#include "geom/GeoLineSegment.h"
#include "geom/GeoReferenceSystem.h"

#include <cstddef>
#include <memory>

namespace ep {
namespace geom {

class GeoLineString : public GeoGeometry
{
  friend class GeoFactory;

public:
  using Ptr = std::unique_ptr<GeoLineString>;

  /** \brief
   * The minimum number of vertices allowed in a valid non-empty ring.
   * Empty rings with 0 vertices are also valid.
   */
  static const unsigned int MINIMUM_VALID_SIZE = 3;

  ~GeoLineString() override = default;

  std::string getGeometryType() const override;

  std::size_t getNumCoordinate() const;

  GeoCoordinate       *getCoordinate(std::size_t index);
  const GeoCoordinate *getCoordinate(std::size_t index) const;

  GeoCoordinateSequence       *getCoordinates();
  const GeoCoordinateSequence *getCoordinates() const;

  std::unique_ptr<GeoPoint>       getPoint(std::size_t index) const;
  std::unique_ptr<GeoLineSegment> getLineSegment(std::size_t index) const;

  virtual bool isClosed() const;

  virtual bool isRing() const;

#ifdef EP_OPENGL
  void draw() const override;
#endif

protected:
  GeoLineString(
      std::unique_ptr<GeoCoordinateSequence> &&pts, GeoReferenceSystem ref);

protected:
  std::unique_ptr<GeoCoordinateSequence> pts_;
};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_GEOLINESTRING_H_