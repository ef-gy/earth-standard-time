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

// Optional server features.
#include <cxxhttp/httpd-options.h>
#include <cxxhttp/httpd-quit.h>
#include <cxxhttp/httpd-trace.h>

#include <est/httpd-est.h>

int main(int argc, char *argv[]) { return cxxhttp::io::main(argc, argv); }
