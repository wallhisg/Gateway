#ifndef REPLY_H_
#define REPLY_H_

#include <string>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>

#include "Buffer.h"

namespace asio = boost::asio;

namespace TcpServer {

class Connection;
class Request;
class Reply;

typedef boost::shared_ptr<Connection> ConnectionPtr;
typedef boost::shared_ptr<Reply> ReplyPtr;

class Reply : public boost::enable_shared_from_this<Reply>
{
public:
    Request& request_;
    Reply(Request &request);
    virtual ~Reply();
    
    void setConnection(ConnectionPtr connection);
    
protected:
    ReplyPtr replay() const { return replay_; }
    ConnectionPtr connection() const { return connections_; }
    
private:
    
    std::vector<Header> headers_;
    ConnectionPtr connections_;
    ReplyPtr replay_;
    
};

typedef boost::shared_ptr<Reply> ReplyPtr;

}   // namespace TcpServer


#endif // REPLY_H_
