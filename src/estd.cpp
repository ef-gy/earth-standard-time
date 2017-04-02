/**\file
 * \brief Earth Standard Time Server
 *
 * Call it like this:
 * \code
 * $ ./estd http:localhost:8080
 * \endcode
 *
 * \copyright
 * This file is part of the ESTd project, which is released as open source
 * under the terms of an MIT/X11-style licence, described in the COPYING file.
 *
 * \see Documentation: https://ef.gy/documentation/earth-standard-time
 * \see Source Code: https://github.com/ef-gy/earth-standard-time
 * \see Licence Terms: https://github.com/ef-gy/earth-standard-time/COPYING
 */

#define ASIO_DISABLE_THREADS
#include <cxxhttp/httpd.h>
#include <est/time.h>
#include <ef.gy/render-json.h>

using namespace cxxhttp;
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

  bool useJSON = (m[3] == ".json");
  std::map<std::string,std::string> head = {};

  if (useJSON) {
    json::value<> v;
    v.toObject();

    v("year") = t.year();
    v("month") = t.month();
    v("day") = t.day();

    v("hour") = t.hour();
    v("minute") = t.minute();
    v("second") = t.second();

    v("is-month-named") = t.isMonthNamed();

    os << json::tag() << v;
    head["Content-Type"] = "application/json";
  } else {
    os << t.year() << "-" << t.month() << "-" << t.day() << " " << t.hour()
       << ":" << t.minute() << ":" << t.second();
    head["Content-Type"] = "text/plain";
  }

  session.reply(200, head, os.str());

  return true;
}

static const char *rx = "/est(/unix/(-?[0-9]+))?(\\.json)?";

static httpd::servlet<asio::ip::tcp> TCPEST(rx,
                                            EST<asio::ip::tcp>);
static httpd::servlet<asio::local::stream_protocol>
    UNIXEST(rx, EST<asio::local::stream_protocol>);

int main(int argc, char *argv[]) { return io::main(argc, argv); }
