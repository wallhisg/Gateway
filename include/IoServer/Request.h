#ifndef REQUEST_H_
#define REQUEST_H_

#include <string>
#include <map>
#include <vector>
#include <list>
#include <IoServer/Buffer.h>

using namespace std;

namespace TcpServer {
    


class Request
{
public:
    enum State { Partial, Complete, Error};

    
    Request();
    
    void reset();
    
    std::vector<Header> headers_;
    string remoteIP;
    short port;
private:

};
    
}   // namespace TcpServer

#endif // REQUEST_H_
