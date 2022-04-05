#ifndef ELLIPSOID_UTIL_MACRO_H_
#define ELLIPSOID_UTIL_MACRO_H_

#include <ostream>
#include <sstream>

namespace ep {
namespace util {
    
/**
 * @brief Macro expansion to a toString class method
 */
#define TO_STRING_METHOD_WITH_OSTREAM(CLASS_NAME)                        \
    friend std::ostream &operator<<(std::ostream &, const CLASS_NAME &); \
    std::string toString() const                                         \
    {                                                                    \
        std::ostringstream s;                                            \
        s << *this;                                                      \
        return s.str();                                                  \
    }

/**
 * @brief  Virtual macro expansion to a toString class method
 */
#define TO_STRING_VIRTUAL_METHOD_WITH_OSTREAM(CLASS_NAME)                \
    friend std::ostream &operator<<(std::ostream &, const CLASS_NAME &); \
    virtual std::string toString() const                                 \
    {                                                                    \
        std::ostringstream s;                                            \
        s << *this;                                                      \
        return s.str();                                                  \
    }

} // namespace util
} // namespace ep

#endif