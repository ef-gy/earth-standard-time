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

#if !defined(EST_HTTPD_EST_H)
#define EST_HTTPD_EST_H

#include <sstream>

#include <cxxhttp/httpd.h>
#include <est/json.h>
#include <est/string.h>

#include <ef.gy/stream-json.h>

namespace est {
namespace http {
template <class transport>
static bool
EST(typename cxxhttp::net::http::server<transport>::session &session,
    std::smatch &m) {
  std::ostringstream os("");

  est::time<> t = est::time<>::now();

  if (m[1] != "") {
    t = est::time<>::fromUNIX(std::stold(m[2]));
  }

  bool useJSON = (m[3] == ".json");
  cxxhttp::headers head = {};

  if (useJSON) {
    os << efgy::json::tag() << toJSON(t);
    head["Content-Type"] = "application/json";
  } else {
    os << toString(t);
    head["Content-Type"] = "text/plain";
  }

  session.reply(200, head, os.str());

  return true;
}

static const char *regex = "/est(/unix/(-?[0-9]+))?(\\.json)?";

static cxxhttp::httpd::servlet<asio::ip::tcp> TCP(regex, EST<asio::ip::tcp>);
static cxxhttp::httpd::servlet<asio::local::stream_protocol>
    UNIX(regex, EST<asio::local::stream_protocol>);
}
}

#endif
