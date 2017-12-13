#ifndef REQUEST_PARSER_H_
#define REQUEST_PARSER_H_

#include <iostream>
#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>
#include <IoServer/Buffer.h>
#include <IoServer/Request.h>

static std::size_t MAX_REQUEST_SIZE = 112*1024;

using namespace std;
namespace TcpServer {
    
class RequestParser
{
public:
    RequestParser();
    void reset();
    /*  
     * Parse some data. The tribool return value is true when a complete request
     * has been parsed, false if the data is invalid, indeterminate when more 
     * data is required. The iterator return value indicates how much of the 
     * input has been consumed.
    */

    boost::tuple<boost::tribool, Buffer::iterator> parser(Request &req,
                                                          Buffer::iterator begin, 
                                                          Buffer::iterator end);
private:
    
    // Handle the next character of input.
    boost::tribool consume(Request& req, Buffer::iterator it);
    
    // Check if a byte is an character.
    static bool is_char(int c);
    
    // Check if a byte is an control character
    static bool is_ctrl(int c);
    
    // Check if a byte is a tspecial character
    static bool is_tspecial(int c);
    
    // Check if a byte is a digit
    static bool is_digit(int c);
    
    
    
    Request::State parserTcpMessage(Request req);
    Request::State parserMqttMessage(Request req);
    
    // Select Protocol JSON or MQTT
    enum proto_flags
    {
        json,
        mqtt
        
    } proto_flag_;
    
    // The current state of the parser.
    enum state
    {
        method_start,
        method,
        header_line_start,
        header_value
    } state_;
    
    // The current state of the request parser.
    
    enum tcp_state
    {
        tcp_start,
        tcp_newline_0
        
        
    } tcp_state_;
    
    typedef struct
    {
        tcp_state tcp_state_;
        int count;
        bool flag;
    } tcp_state_t;
    
    enum mqtt_state
    {
        mqtt_start
        
    } mqtt_state_;
    
    unsigned int tcp_size_;
};
    
}



#endif // REQUEST_PARSER_H_
