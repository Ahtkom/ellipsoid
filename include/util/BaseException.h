#ifndef ELLIPSOID_UTIL_BASEEXCEPTION_H_
#define ELLIPSOID_UTIL_BASEEXCEPTION_H_

#include <stdexcept>
#include <string>

namespace ep {
namespace util {
    
class BaseException : public std::runtime_error
{
public:
    BaseException()
        : std::runtime_error("Unkown error")
    {}

    BaseException(std::string const &msg)
        : std::runtime_error(msg)
    {}

    BaseException(std::string const &name, std::string const &msg)
        : std::runtime_error(name + ": " + msg)
    {}

    ~BaseException() = default;
};


} // namespace util
} // namespace ep


#endif