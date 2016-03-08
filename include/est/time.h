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

#if !defined(EST_TIME_H)
#define EST_TIME_H

#include <est/orbit.h>
#include <est/moon.h>

namespace est {
template <class Q = long double, class clock = std::chrono::system_clock>
class time : public base<Q, clock> {
public:
  constexpr time(const Q &pValue) : base<Q, clock>(pValue) {}
  constexpr time(const base<Q, clock> &pValue) : base<Q, clock>(pValue) {}

  Q second(void) const { return std::floor(std::fmod(getDayPortion(), 60.l)); }

  Q minute(void) const {
    return std::floor(std::fmod(getDayPortion() / 60.l, 60.l));
  }

  Q hour(void) const { return std::floor(getDayPortion() / 3600.l); }

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
    Q ls = lunarLeapSeconds() + solarQuartersSinceEpoch() * 43.l * 60.l;

    const Q os = orbit::secondsSinceLastQuarter(toTerrestrial());

    if (os < 3.l * 3600.l) {
      ls -= 43.l * 60.l;

      Q p = std::fmod(value - ls, 60.l * 1444.l),
        h1 = std::floor((p - os) / 3600.l), h2 = std::fmod((p - os), 3600.l),
        nextFullHour = h1 > 23.l ? 4.l * 60.l - h2 : 3600.l - h2,
        s = os - nextFullHour, m = std::floor(s / 60.l);

      ls += nonPrimeLeapMinutes(m) * 60.l;
    }

    return ls;
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

  Q lunarLeapSeconds(void) const {
    Q ls = fullMoonsSinceEpoch() * 8.l * 3600.l;

    const Q sf = moon::secondsSinceFullMoon(toTerrestrial());

    if (sf < 4.l * 3600.l) {
      ls -= 8.l * 3600.l - sf * 2.l;
    }

    return ls;
  }

  static bool isPrime(long m) {
    if (m <= 1) {
      return false;
    }

    for (long i = 2; i <= std::sqrt(m); i++) {
      if ((m % i) == 0) {
        return false;
      }
    }

    return true;
  }

  static Q nonPrimeLeapMinutes(long m) {
    if (m < 0) {
      return 0;
    }

    if (m > (60 + 43)) {
      return 43;
    }

    long l = 0;
    bool jd = false;

    for (long i = 0; i < m; i++) {
      if (!jd && !isPrime(i - l)) {
        l++;
        jd = true;
      } else {
        jd = false;
      }
    }

    return l;
  }

  Q secondsWithoutLeapSeconds(void) const { return value - leapSeconds(); }

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
