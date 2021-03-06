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

    BaseException(std::string const &name, const std::string &func, const std::string &msg)
        : std::runtime_error(name + ": in \"" + func + "\"\n" + msg)
    {}

    ~BaseException() = default;
};


} // namespace util
} // namespace ep


#endif