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

#if !defined(EST_TIME_H)
#define EST_TIME_H

#include <est/orbit.h>
#include <est/moon.h>

namespace est {
template<class Q = long double, class clock = std::chrono::system_clock>
class time : public base<Q, clock> {
public:
  constexpr time(const Q &pValue) : base<Q, clock>(pValue) {}
  constexpr time(const base<Q, clock> &pValue) : base<Q, clock>(pValue) {}

  Q second(void) const {
    return std::floor(std::fmod(getDayPortion(), 60.l));
  }

  Q minute(void) const {
    return std::floor(std::fmod(getDayPortion() / 60.l, 60.l));
  }

  Q hour(void) const {
    return std::floor(getDayPortion() / 3600.l);
  }

  Q day(void) const {
    return 1.l + std::floor(std::fmod(getDatePortion(), 30.l));
  }

  Q month(void) const {
    return 1.l + std::floor(std::fmod(getDatePortion() / 30.l, 12.l));
  }

  Q year(void) const {
    return 1970.l + std::floor(getDatePortion() / (30.l * 12));
  }

  Q leapSeconds(void) const {
    return fullMoonsSinceEpoch() * 8.l * 3600.l
         + solarQuartersSinceEpoch() * 43 * 60.l;
  }

  using base<Q, clock>::toTerrestrial;
  using base<Q, clock>::epoch;

protected:
  Q fullMoons(void) const {
    return std::floor(moon::fullMoon(toTerrestrial()));
  }

  Q fullMoonsSinceEpoch(void) const {
    return -time(epoch()).fullMoons() + fullMoons();
  }

  Q solarQuarters(void) const {
    return std::floor(orbit::asQuarter(toTerrestrial()));
  }

  Q solarQuartersSinceEpoch(void) const {
    return -time(epoch()).solarQuarters() + solarQuarters();
  }

  Q secondsWithoutLeapSeconds(void) const {
    return value - leapSeconds();
  }

  Q getDatePortion(void) const {
    return std::floor(secondsWithoutLeapSeconds() / (1444.l * 60.l));
  }

  Q getDayPortion(void) const {
    return std::fmod(secondsWithoutLeapSeconds(), 60.l * 1444.l);
  }

protected:
  using base<Q, clock>::value;
};
}

#endif
