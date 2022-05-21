#ifndef ELLIPSOID_IO_PARSEEXCEPTION_H_
#define ELLIPSOID_IO_PARSEEXCEPTION_H_

#include <util/BaseException.h>

namespace ep {
namespace io {

class ParseException : public util::BaseException {
public:
  // ParseException()
  //     : util::BaseException("ParseException", "")
  // {}

  /**
   * @example
   *   throw ParseException(__PRETTY_FUNCTION__, msg);
   */
  ParseException(const std::string &func, const std::string &msg)
      : util::BaseException("ParseException", func, msg) {}

  ~ParseException() noexcept override {}
};

} // namespace io
} // namespace ep

#endif // ELLIPSOID_IO_PARSEEXCEPTION_H_