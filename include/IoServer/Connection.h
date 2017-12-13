#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

#include <iostream>
#include <string>
#include <list>

#include <IoServer/IoFlags.h>
#include <IoServer/TypeDef.h>
#include <IoServer/Request.h>
#include <IoServer/RequestParser.h>

namespace TcpServer {
    
class ConnectionManager;

using namespace std;

namespace asio = boost::asio;

typedef boost::system::error_code asio_error_code;
typedef boost::system::system_error asio_system_error;
typedef boost::asio::deadline_timer asio_timer;
typedef boost::posix_time::milliseconds asio_timer_milliseconds;

class Connection
    :   public boost::enable_shared_from_this<Connection>,
        private boost::noncopyable
{
public:
    explicit Connection(asio::io_service &service, ConnectionManager &manager);
    virtual ~Connection();
    // Get the socket associated with the connection.
    virtual asio::ip::tcp::socket &socket() = 0;
    
    // Start the first asynchronous operation for the connection.
    virtual void start();
    

    void close();
    bool closed() const;


protected:
    void handleReadRequest(const asio_error_code &err, std::size_t bytes_transferred);
    void on_read();
    void handleWriteRequest(const asio_error_code &err, std::size_t bytes_transferred);

    void setReadTimeout(int seconds);
    void setWriteTimeout(int seconds);
    
    ConnectionManager &connectionManager_;
    
    virtual void stop();
    
    asio::strand strand_;
    
    enum IoState
    {
        Idle = 0x0,
        Reading = 0x01,
        Writing = 0x02
    };
    
    IoFLags<IoState> state_; 
    
private:
    virtual void startAsynReadRequest(Buffer& buffer, int timeout) = 0;
    virtual void startAsynWriteRequest(const std::string &msg) = 0;
    void handleError(const asio_error_code &err);
    
    void cancelReadTimer();
    void cancelWriteTimer();
    
    void timeout(const asio_error_code &err);
    void doTimeout();
    
private:
   
    // Current request buffer data
    std::vector<Buffer> rcv_buffers_;
    
    // Size of last buffer and iterator for next request in last buffer
    std::size_t rcv_buffers_size_;
    Buffer::iterator rcv_remaining_;
    
    // Timer for reading data.
    asio_timer readTimer_, writeTimer_;
    
    // The incoming request.
    Request request_;
    
    // The parser for the incoming request.
     RequestParser request_parser_;
};

typedef boost::shared_ptr<Connection> ConnectionPtr;

}   // namespace TcpServer

#endif
