#ifndef ELLIPSOID_GEOM_GEOENVELOPE_H_
#define ELLIPSOID_GEOM_GEOENVELOPE_H_

namespace ep {
namespace geom {

class GeoEnvelope
{
public:
  void merge(const GeoEnvelope *other);

};

} // namespace geom
} // namespace ep

#endif // ELLIPSOID_GEOM_GEOENVELOPE_H_