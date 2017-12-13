#include <IoServer/RequestParser.h>

namespace TcpServer 
{
    
RequestParser::RequestParser()
    : state_(method_start)
{
    reset();
}

void RequestParser::reset()
{
    state_ = method_start;
    tcp_size_ = 0;
}


boost::tuple<boost::tribool, Buffer::iterator> 
RequestParser::parser(Request &req, 
                                 Buffer::iterator begin, 
                                 Buffer::iterator end)
{
    while(begin != end)
    {
        cout << "Loop parser: "<< endl;
        std::cout << begin << std::endl;
        boost::tribool result = consume(req, begin++);
        if (result || !result)
            return boost::make_tuple(result, begin);
    }
    boost::tribool result = boost::indeterminate;
    return boost::make_tuple(result, begin);
}


boost::tribool RequestParser::consume(TcpServer::Request& req, Buffer::iterator it)
{
    static boost::tribool False(false);
    static boost::tribool True(true);
    static boost::tribool Indeterminate(boost::indeterminate);
    
    const char input = *it;
    cout << "State_: " << state_ << endl;
    cout << "it: " << input << endl;
        
    if (++tcp_size_ > MAX_REQUEST_SIZE)
        return False;
    
    std::cout << "tcp_size_: " << tcp_size_ << endl;
    
    switch (tcp_state_)
    {
        case method_start:
            if (input == '\r')
            {
                /*
                * allow a new line before a request -- this seems to be
                * accepted practice when dealing with multiple requests
                * in one connection, separated by a CRLF.
                */
                tcp_state_ = tcp_newline_0;
                return Indeterminate;
            }
            else if (!is_char(input)) || is_ctrl(input) ||
    }
    
    
}

bool RequestParser::is_char(int c)
{
    return c >= 0 && c <= 127; 
}

bool RequestParser::is_ctrl(int c)
{
    return (c >=0 && c <=31) || (c == 127);
}

bool RequestParser::is_tspecial(int c)
{
    switch (c)
    {
        case '(': case ')': case '<': case '>': case '@':
        case ',': case ';': case ':': case '\\': case '"':
        case '/': case '[': case ']': case '?': case '=':
        case '{': case '}': case ' ': case '\t':
            return true;
        default:
            return false;
    }
}

bool RequestParser::is_digit(int c)
{
    return c >= '0' && c <= '9';
}

} // namespace TcpServer

