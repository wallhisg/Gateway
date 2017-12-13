#include <IoServer/Reply.h>

namespace TcpServer {
    
Reply::Reply(Request &request)
    : request_(request)
{
    
}

Reply::~Reply()
{
    
}

void TcpServer::Reply::setConnection(ConnectionPtr connection)
{
    connections_ = connection;
    
    if (replay_.get())
        replay_->setConnection(connection);
}

}   // namespace TcpServer
