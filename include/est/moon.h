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
  return (
      + fullMoonOffset
      + lunation * month
      + lunationCoFactor * month * month);
}

static constexpr std::array<long double, 2> fullMoons(long double seconds) {
  return {
      ( -std::sqrt(  -4.l * fullMoonOffset * lunationCoFactor
              + lunation * lunation
              + 4.l * lunationCoFactor * seconds)
        - lunation)
      / (2.l * lunationCoFactor),
      ( std::sqrt(  -4.l * fullMoonOffset * lunationCoFactor
              + lunation * lunation
              + 4.l * lunationCoFactor * seconds)
        - lunation)
      / (2.l * lunationCoFactor)
      };
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
