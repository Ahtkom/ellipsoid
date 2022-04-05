#include <algorithm/alg.h>
#include <algorithm>
#include <math.h>

namespace ep {

double toDegree(double rad)
{
    return rad * 180 / PI;
}

double toRadius(double deg)
{
    return deg / 180 * PI;
}
    
} // namespace ep