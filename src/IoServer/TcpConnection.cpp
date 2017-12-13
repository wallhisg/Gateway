#include <IoServer/TcpConnection.h>

namespace TcpServer {
    
TcpConnection::TcpConnection(asio::io_service &service, ConnectionManager &manager)
    :   Connection(service, manager),
        socket_(service)
{
    cout << "TcpConnection::TcpConnection" << endl;
}

asio::ip::tcp::socket & TcpConnection::socket()
{
    return socket_;
}

void TcpConnection::stop()
{
    try {
        boost::system::error_code  ignored_ec;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
        socket_.close();
    }
    catch(asio_error_code &e) {
        
    }
    Connection::stop();
}

void TcpConnection::startAsynReadRequest(Buffer& buffer, int timeout)
{
    if (state_ & Reading)
    {   
        stop();
        return;
    }
    
    setReadTimeout(timeout);
    
    boost::shared_ptr<TcpConnection> sft = boost::dynamic_pointer_cast<TcpConnection>(shared_from_this());
    
    socket_.async_read_some(asio::buffer(buffer), 
                            strand_.wrap(boost::bind(&TcpConnection::handleReadRequest, 
                                                     sft, asio::placeholders::error, 
                                                     asio::placeholders::bytes_transferred)));
}

void TcpConnection::startAsynWriteRequest(const std::string& msg)
{
}

}   // namespace TcpServer
