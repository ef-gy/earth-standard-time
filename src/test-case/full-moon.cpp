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

#include <iostream>

#include <ef.gy/test-case.h>
#include <ef.gy/range.h>

#include <est/moon.h>

using namespace est::moon;

int testFullMoon(std::ostream &log) {
  long double minDeviation = 9999;
  long double maxDeviation = 0;

  for (long double i : efgy::range<long double>(-20000, 20000, 40000)) {
    long double s = terrestrialFullMoon(i);
    long double r = fullMoon(s);
    long double dev = i - r;

    minDeviation = std::min(minDeviation, std::abs(dev));
    maxDeviation = std::max(maxDeviation, std::abs(dev));
  }

  log << "minimum deviation (fullMoon(terrestrialFullMoon)): " << minDeviation
      << "\n";
  log << "maximum deviation (fullMoon(terrestrialFullMoon)): " << maxDeviation
      << "\n";

  return maxDeviation > 0.0001;
}

TEST_BATCH(testFullMoon)
