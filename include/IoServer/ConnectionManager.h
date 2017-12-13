#ifndef CONNECTION_MANAGER_H_
#define CONNECTION_MANAGER_H_

#include <set>
#include <boost/thread/mutex.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <IoServer/Connection.h>

using namespace std;

namespace TcpServer {

class ConnectionManager
    : private boost::noncopyable
{
public:
    // Add the specified connection to the manager and start it.
    void start(ConnectionPtr c);
    
    // Stop the specified connection.
    void stop(ConnectionPtr c);
    
    // Stop all connections.
    void stopAll();
    
private:
    set<ConnectionPtr> connections_;
    boost::mutex mutex_;
};

}   // namespace TcpServer

#endif
