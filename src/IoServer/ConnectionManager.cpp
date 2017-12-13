#include <IoServer/ConnectionManager.h>

namespace TcpServer {
    
void ConnectionManager::start(ConnectionPtr c)
{
    boost::mutex::scoped_lock lock(mutex_);
    connections_.insert(c);
    lock.unlock();
    
    c->start();
    cout << "ConnectionManager::start" << endl;
}

void ConnectionManager::stop(ConnectionPtr c)
{
    boost::mutex::scoped_lock lock(mutex_);
    
    set<ConnectionPtr>::iterator it = connections_.find(c);
    if (it != connections_.end())
    {
        connections_.erase(it);
    }
    else
        return;
    lock.unlock();
    cout << "ConnectionManager::stop" << endl;
}

void ConnectionManager::stopAll()
{
    for(;;)
    {
        ConnectionPtr ptr;
        {
            boost::mutex::scoped_lock lock(mutex_);
            
            if (connections_.size())
                ptr = *connections_.begin();
        }
        if (ptr)
            stop(ptr);
        else
            break;
    }
}

}   // namespace TcpServer
