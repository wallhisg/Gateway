#ifndef TYPE_DEF_H_
#define TYPE_DEF_H_

#include <boost/asio.hpp>
#include <boost/array.hpp>

static const int CONNECTION_TIMEOUT = 2000; // 2 seconds
static const int KEEPALIVE_TIMEOUT  = 200;  // 500 milliseconds

#define BUFFER_SIZE 8192
typedef boost::array<char,  BUFFER_SIZE> Buffer;

#endif
