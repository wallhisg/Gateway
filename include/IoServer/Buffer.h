#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>

namespace TcpServer {
    
typedef boost::array<char, 8192> Buffer;

struct buffer_string
{
    char *data;
    unsigned int len;
    buffer_string *next;
    
    buffer_string()
        : data(0), len(0), next(0) 
    {}
    
    void clear() { data =0; len = 0; next = 0; }
    
};

struct Header {
    buffer_string name;
    buffer_string value;
};

}   // namespace TcpServer

#endif // TCP_SERVER_H_
