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

#if !defined(EST_BASE_H)
#define EST_BASE_H

#include <chrono>
#include <cmath>

/**
 * Note: the epoch of this is *probably* 1970-01-01 00:00:00 UTC and it's
 * *probably* not counting leap seconds.
 */
namespace est {
template <class Q = long double, class clock = std::chrono::system_clock>
class base {
public:
  constexpr base(const Q &pValue) : value(pValue) {}

  static constexpr base fromUNIX(const Q &value) {
    return base(value + unixToJulianOffset);
  }

  static constexpr base fromJulian(const Q &value) {
    return fromUNIX(value / 86400.l + 2440587.5l);
  }

  static constexpr base epoch(void) { return base(Q(0)); }

  static constexpr base now(void) {
    return fromUNIX(flatten(clock::now().time_since_epoch()));
  }

  constexpr Q toUNIX(void) const { return value - unixToJulianOffset; }

  constexpr Q toTerrestrial(void) const {
    return toUNIX() + 36 // TAI to UTC offset in Q3 2015
           // leap seconds are not actually in the UNIX base stamp, so we weould
           // not have needed to add those leap seconds since 1970 to the time
           // stamp to get to TAI.
           - 26     // number of leap seconds in Q3 2015
           + 32.184 // offset between TAI and TT, Q3 2015
           // finally, convert to seconds since January 1st, 2000, which makes
           // it
           // easier plug into our formula for the moon phases.
           - unixToTerrestrialEpochOffset;
  }

  constexpr Q toJulian(void) const { return (toUNIX() - 2440587.5l) * 86400.l; }

  static Q flatten(const typename clock::duration &d) {
    return Q(d.count()) * Q(clock::period::num) / Q(clock::period::den);
  }

protected:
  Q value;

  static constexpr const long long unixToJulianOffset = -1123200;
  static constexpr const long long unixToTerrestrialEpochOffset = 946684800;
};

template <class clock = std::chrono::system_clock, typename Q = long double>
long double terrestrial(const typename clock::time_point &t) {
  return base<Q>::fromUNIX(base<Q>::flatten(t.time_since_epoch()))
      .toTerrestrial();
}

template <class clock = std::chrono::system_clock>
long double terrestrial(void) {
  return terrestrial(clock::now());
}
}

#endif
