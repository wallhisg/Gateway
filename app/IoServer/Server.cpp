#include <IoServer/IoServer.h>
#include <Wt/WServer>
#include <Wt/WIOService>
#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WContainerWidget>
#include <Wt/WText>

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>


using namespace Wt;
using namespace std;
using namespace TcpServer;

class Server : boost::noncopyable
{
public:
    Server(WServer &server, TcpServer::IoServer &ioServer)
        : server_(server), ioServer_(ioServer)
    {

    }
    
private:
    WServer &server_;
    TcpServer::IoServer  &ioServer_;
};

class ServerWidget : public WContainerWidget
{
public:
    ServerWidget(Server& server, Wt::WContainerWidget *parent = 0)
        : server_(server), WContainerWidget(parent)
    {
        WText *txtText = new WText("Server Widget");
        this->addWidget(txtText);
    }
    
private:
    Server& server_;
};

class ServerApplication : public WApplication
{
public:
    ServerApplication(const WEnvironment& env, Server& server)
        : WApplication(env),
          server_(server)
    {

        serverWidget = new ServerWidget(server_, root());
    }

private:
    Server& server_;
    ServerWidget* serverWidget;

};

WApplication *createApplication(const WEnvironment& env,
                Server& server) {
    return new ServerApplication(env, server);
}

int main(int argc, char **argv)
{
    WServer server(argv[0]);
    server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
    TcpServer::IoServer  ioServer(server.ioService());
    Server webServer(server, ioServer);
    
    server.addEntryPoint(Wt::Application,
            boost::bind(createApplication, _1,
                    boost::ref(webServer)));
    
    if (server.start()) 
    {
        int sig = Wt::WServer::waitForShutdown();
        std::cerr << "Shutting down: (signal = " << sig << ")" << std::endl;
        server.stop();
    }
}
