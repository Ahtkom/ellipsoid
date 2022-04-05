#ifndef ELLIPSOID_IO_PARSEEXCEPTION_H_
#define ELLIPSOID_IO_PARSEEXCEPTION_H_

#include <util/BaseException.h>

namespace ep {
namespace io {
    
class ParseException : public util::BaseException
{
public:
    ParseException()
        : util::BaseException("ParseException", "")
    {}

    ParseException(const std::string &msg)
        : util::BaseException("ParseException", msg)
    {}

    ~ParseException() noexcept override {}
};

    
} // namespace io
} // namespace ep

#endif