#ifndef ELLIPSOID_UTIL_ILLEGALARGUMENTEXCEPTION_H_
#define ELLIPSOID_UTIL_ILLEGALARGUMENTEXCEPTION_H_

#include <util/BaseException.h>

namespace ep {
namespace util {
    
class IllegalArgumentException : public BaseException
{
public:
    IllegalArgumentException()
        : BaseException("IllegalArgumentException", "")
    {}

    IllegalArgumentException(const std::string &msg)
        : BaseException("IllegalArgumentException", msg)
    {}

    ~IllegalArgumentException() noexcept override {}
};

    
} // namespace util
} // namespace ep


#endif