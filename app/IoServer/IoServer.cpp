
#include <IoServer/IoServer.h>

namespace TcpServer {
    
IoServer::IoServer(asio::io_service &service)
    :   service_(service), tcp_acceptor_(service),
        accept_strand_(service)
{
    cout << "************************" << endl;
    start();
}

asio::io_service & IoServer::service()
{
    return service_;
}

// Public members
void IoServer::start()
{
    asio::ip::tcp::endpoint tcp_endpoint;
    tcp_endpoint = asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8001);
    tcp_acceptor_.open(tcp_endpoint.protocol());
    tcp_acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    tcp_acceptor_.bind(tcp_endpoint);
    tcp_acceptor_.listen();
    
    new_tcpconnection_.reset(new TcpConnection(service_, connection_manager_));
    service_.post(boost::bind(&IoServer::startAccept, this));
}

void IoServer::stop()
{
    service_.post(accept_strand_.wrap(boost::bind(&IoServer::handleStop, 
                                                this)));
}

void IoServer::resume()
{
    service_.post(boost::bind(&IoServer::handleResume, this));
}

void IoServer::handleResume()
{
    tcp_acceptor_.close();
    
    start();
}


// Private members
void IoServer::startAccept()
{
    if (new_tcpconnection_)
    {
        tcp_acceptor_.async_accept(new_tcpconnection_->socket(), 
                                accept_strand_.wrap(boost::bind(&IoServer::handleTcpAccept, 
                                                                this, 
                                                                asio::placeholders::error)));
    }
}

void IoServer::handleTcpAccept(const asio_error_code& e)
{
    if (!e)
    {
        connection_manager_.start(new_tcpconnection_);
        new_tcpconnection_.reset(new TcpConnection(service_, connection_manager_));
        tcp_acceptor_.async_accept(new_tcpconnection_->socket(), 
                                accept_strand_.wrap(boost::bind(&IoServer::handleTcpAccept, 
                                                                this, 
                                                                asio::placeholders::error())));
    }
}

void IoServer::handleStop()
{
    tcp_acceptor_.close();
    connection_manager_.stopAll();
}

int IoServer::tcpLocalPort() const
{
    return tcp_acceptor_.local_endpoint().port();
}

}   // namespace TcpServer
