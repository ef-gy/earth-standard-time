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

#if !defined(EST_JSON_H)
#define EST_JSON_H

#include <ef.gy/json.h>
#include <est/time.h>

namespace est {
template <class Q = long double, class clock = std::chrono::system_clock>
static inline efgy::json::json toJSON(const time<Q, clock> &time) {
  efgy::json::json v;
  v.toObject();

  v("year") = time.year();
  v("month") = time.month();
  v("day") = time.day();

  v("hour") = time.hour();
  v("minute") = time.minute();
  v("second") = time.second();

  v("is-month-named") = time.isMonthNamed();

  return v;
}

template <class Q = long double, class clock = std::chrono::system_clock>
static inline std::vector<time<Q, clock>> fromJSON(const efgy::json::json &v) {
  std::vector<time<Q, clock>> ts = {};

  return ts;
}
}

#endif
