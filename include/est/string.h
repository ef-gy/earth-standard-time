/**\file
 *
 * \copyright
 * This file is part of the ESTd project, which is released as open source
 * under the terms of an MIT/X11-style licence, described in the COPYING file.
 *
 * \see Documentation: https://ef.gy/documentation/earth-standard-time
 * \see Source Code: https://github.com/ef-gy/earth-standard-time
 * \see Licence Terms: https://github.com/ef-gy/earth-standard-time/COPYING
 */

#if !defined(EST_STRING_H)
#define EST_STRING_H

#include <est/time.h>
#include <sstream>

namespace est {
template <class Q = long double, class clock = std::chrono::system_clock>
static inline std::string toString(const time<Q, clock> &time) {
  std::ostringstream os("");

  os << time.year() << "-" << time.month() << "-" << time.day() << " "
     << time.hour() << ":" << time.minute() << ":" << time.second();

  return os.str();
}

template <class Q = long double, class clock = std::chrono::system_clock>
static inline std::vector<time<Q, clock>> fromString(const std::string &s) {
  std::vector<time<Q, clock>> ts = {};

  return ts;
}
}

#endif
