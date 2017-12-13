#ifndef TCP_CONNECTION_H_
#define TCP_CONNECTION_H_

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <IoServer/Connection.h>

namespace asio = boost::asio;

namespace TcpServer {
    
class TcpConnection : public Connection
{
public:
    explicit TcpConnection(asio::io_service &service, ConnectionManager &manager);
    virtual asio::ip::tcp::socket& socket();
    
protected:
    virtual void startAsynReadRequest(Buffer& buffer, int timeout);
    virtual void startAsynWriteRequest(const std::string & msg);
    
    virtual void stop();
    
    asio::ip::tcp::socket socket_;
};

typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;

}   // namespace TcpServer

#endif
