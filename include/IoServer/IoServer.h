#ifndef IOSERVER_H_
#define IOSERVER_H_

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include <string>

#include "TcpConnection.h"
#include "ConnectionManager.h"

using namespace std;


namespace asio = boost::asio;
using namespace boost::posix_time;
typedef boost::system::error_code asio_error_code;



namespace TcpServer {
    
class IoServer;

typedef IoServer self_type;
typedef boost::shared_ptr<IoServer> ptr;

class IoServer : 
    public boost::enable_shared_from_this<IoServer>,
    private boost::noncopyable
{
public:
    
    explicit IoServer(asio::io_service &services);
    void start();
    
    // Stop the IoServer.
    void stop();
    // Assumes accept sockets have been closed and reopens them.
    void resume();
    
    asio::io_service &service();
    
private:
    // Starts accepting http/https connections
    void startAccept();
    // Handle completion of an asynchronous accept operation.
    void handleTcpAccept(const asio_error_code &e);
    // Handle a request to stop the server.
    void handleStop();
    // Handle a request to resume the server.
    void handleResume();
    // Returns the tcp local port number.
    int tcpLocalPort() const;
private:
    asio::io_service &service_;
    
    // The strand for handleTcpAccept(), handleSslAccept() and handleStop()
    asio::strand accept_strand_;
    
    // Acceptor used to listen for incoming tcp connections.
    asio::ip::tcp::acceptor tcp_acceptor_;
    
    ConnectionManager connection_manager_;
    
    TcpConnectionPtr new_tcpconnection_;
    // The connection manager which owns all live connections.
    
};
    
}   // namespace TcpServer
#endif

