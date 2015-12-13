/**\file
 *
 * \copyright
 * Copyright (c) 2015, Magnus Achim Deininger <magnus@ef.gy>
 * \copyright
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * \copyright
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * \copyright
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * \see Documentation: https://ef.gy/documentation/earth-standard-time
 * \see Source Code: https://github.com/ef-gy/earth-standard-time
 * \see Licence Terms: https://github.com/ef-gy/earth-standard-time/COPYING
 */

#include <iostream>

#include <ef.gy/test-case.h>
#include <ef.gy/range.h>

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
