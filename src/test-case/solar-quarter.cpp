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

#include <ef.gy/range.h>
#include <ef.gy/test-case.h>

#include <est/orbit.h>

using namespace est::orbit;

int testFullMoon(std::ostream &log) {
  long double minDeviation = 9999;
  long double maxDeviation = 0;

  for (long double i : efgy::range<long double>(-20000, 20000, 40000)) {
    long double s = terrestrialQuarter(i);
    long double r = asQuarter(s);
    long double dev = i - r;

    minDeviation = std::min(minDeviation, std::abs(dev));
    maxDeviation = std::max(maxDeviation, std::abs(dev));
  }

  log << "minimum deviation (asQuarter(terrestrialQuarter)): " << minDeviation
      << "\n";
  log << "maximum deviation (asQuarter(terrestrialQuarter)): " << maxDeviation
      << "\n";

  return maxDeviation > 0.0001;
}

TEST_BATCH(testFullMoon)
