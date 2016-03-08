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

#if !defined(EST_MOON_H)
#define EST_MOON_H

#include <est/base.h>

#include <array>

namespace est {
namespace moon {
static constexpr const long double fullMoonOffset = 1.759359e6l;
/**
 * Average time for a full synodic month, around these days.
 */
static constexpr const long double lunation = 2.551442878e6l;
static constexpr const long double lunationCoFactor = 8.815e-6l;

static constexpr long double terrestrialFullMoon(long double month) {
  return (+fullMoonOffset + lunation * month +
          lunationCoFactor * month * month);
}

static constexpr std::array<long double, 2> fullMoons(long double seconds) {
  return {(-std::sqrt(-4.l * fullMoonOffset * lunationCoFactor +
                      lunation * lunation + 4.l * lunationCoFactor * seconds) -
           lunation) /
              (2.l * lunationCoFactor),
          (std::sqrt(-4.l * fullMoonOffset * lunationCoFactor +
                     lunation * lunation + 4.l * lunationCoFactor * seconds) -
           lunation) /
              (2.l * lunationCoFactor)};
}

static long double fullMoon(long double seconds) {
  const auto months = fullMoons(seconds);
  return std::max(months[0], months[1]);
}

static long double secondsSinceFullMoon(long double seconds) {
  long double month = fullMoon(seconds);
  long double nearest = std::floor(month);
  return seconds - terrestrialFullMoon(nearest);
}
}
}

#endif
