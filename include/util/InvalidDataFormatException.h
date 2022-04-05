#ifndef ELLIPSOID_UTIL_INVALIDDATAFORMATEXCEPTION_H_
#define ELLIPSOID_UTIL_INVALIDDATAFORMATEXCEPTION_H_

#include <util/BaseException.h>

namespace ep {
namespace util {
    
class InvalidDataFormatException : public BaseException
{
public:
    InvalidDataFormatException()
        : BaseException("InvalidDataFormatException", "")
    {}

    InvalidDataFormatException(const std::string &msg)
        : BaseException("InvalidDataFormatException", msg)
    {}

    ~InvalidDataFormatException() noexcept override {}
};

    
} // namespace util
} // namespace ep


#endif