/**\file
 * \brief Earth Standard Time Server
 *
 * Call it like this:
 * \code
 * $ ./estd http:localhost:8080
 * \endcode
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

#define ASIO_DISABLE_THREADS
#include <ef.gy/httpd.h>
#include <est/time.h>

using namespace efgy;

static httpd::servlet<asio::local::stream_protocol>
    unixQuit("/quit", httpd::quit<asio::local::stream_protocol>);

template <class transport>
static bool EST(typename net::http::server<transport>::session &session,
                std::smatch &m) {
  std::ostringstream os("");

  est::time<> t = est::time<>::now();

  if (m[1] != "") {
    t = est::time<>::fromUNIX(std::stold(m[2]));
  }

  os << t.year() << "-" << t.month() << "-" << t.day() << " " << t.hour() << ":"
     << t.minute() << ":" << t.second();
  //  os << "\n" << t.leapSeconds() << "\n"
  //     << t.fullMoonsSinceEpoch() << "\n" << t.solarQuartersSinceEpoch();

  session.reply(200, os.str());

  return true;
}

static httpd::servlet<asio::ip::tcp> TCPEST("/est/(unix/(-?[0-9]+))?",
                                            EST<asio::ip::tcp>);
static httpd::servlet<asio::local::stream_protocol>
    UNIXEST("/est/(unix/(-?[0-9]+))?", EST<asio::local::stream_protocol>);

int main(int argc, char *argv[]) { return io::main(argc, argv); }
