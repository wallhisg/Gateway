#include <IoServer/Request.h>

namespace TcpServer {
    
Request::Request()
{

    
}

void Request::reset()
{
    headers_.clear();
    
}
    
}   // namespace TcpServer
