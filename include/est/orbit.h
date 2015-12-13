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
