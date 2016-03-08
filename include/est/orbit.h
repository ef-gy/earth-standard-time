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

#if !defined(EST_ORBIT_H)
#define EST_ORBIT_H

#include <est/base.h>

namespace est {
/**
 * I'm doing very crude calculations here, mostly because I can't quite be arsed
 * to do more proper ones. Also we have a pretty large window for this, as for
 * EST all we have to do is find a full hour after the next full moon a few
 * times a year, so the full moon calculation is much more important.
 *
 * That said, this is going to get inaccurate very fast...
 */
namespace orbit {
static constexpr const long double period = 3.1558149e7l;
static constexpr const long double offset = 6.852e6l;

static constexpr long double terrestrialQuarter(long double q) {
  return offset + period * q / 4.l;
}

static constexpr long double asQuarter(long double seconds) {
  return -(4.l * (offset - seconds) / period);
}

static long double secondsSinceLastQuarter(long double seconds) {
  long double q = asQuarter(seconds);
  long double nearest = std::floor(q);
  return seconds - terrestrialQuarter(nearest);
}
}
}

#endif
