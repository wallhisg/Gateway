#include <IoServer/Connection.h>
#include <IoServer/ConnectionManager.h>


namespace TcpServer {
    
Connection::Connection(asio::io_service &service, ConnectionManager &manager)
    :   connectionManager_(manager),
        strand_(service),
        state_(Idle),
        readTimer_(service),
        writeTimer_(service)
{
    
}

Connection::~Connection()
{
    
}

void Connection::start()
{
    
    // Request
    request_.reset();
    try 
    {
        request_.remoteIP = socket().remote_endpoint().address().to_string();
        request_.port = socket().local_endpoint().port();
    }
    catch (std::exception &e)
    {
        
    }
    
    asio_error_code ignored_ec;
    socket().set_option(asio::ip::tcp::no_delay(true), ignored_ec);
    
    rcv_buffers_.push_back(Buffer());
    
    startAsynReadRequest(rcv_buffers_.back(), CONNECTION_TIMEOUT);
}

void Connection::close()
{
    cancelReadTimer();
    cancelWriteTimer();

    connectionManager_.stop(shared_from_this());
    cout << "Connection closed" << endl;
}

bool Connection::closed() const
{
    Connection *self = const_cast<Connection *>(this);
    return !self->socket().is_open();
}

void Connection::stop()
{
    // Clear MessageParse;
}

void Connection::handleReadRequest(const asio_error_code& err, 
                                   std::size_t bytes_transferred)
{
    cout << "Connection::handleReadRequest" << endl;
    cancelReadTimer();
    
    if (!err)
    {
        cout << "do handleReadRequest" << endl;
        
        rcv_remaining_ = rcv_buffers_.back().data();
        rcv_buffers_size_ = bytes_transferred;
        on_read();

        //std::cout << "rcv buffer size: " << rcv_buffers_.size() << '\n';
        //std::cout << "rcv buffer max size: " << rcv_buffers_.max_size() << '\n';
    }
    else if (err != asio::error::operation_aborted && err != asio::error::bad_descriptor)
    {
        handleError(err);
    }
}

void Connection::on_read()
{
        cout << rcv_remaining_  << endl;
        Buffer &buffer = rcv_buffers_.back();
        
        boost::tribool result;
        
        boost::tie(result, rcv_remaining_)
            = request_parser_.parser(request_, 
                                     rcv_remaining_, 
                                     buffer.data() + rcv_buffers_size_);
        // true
        if (result)
        {
            
        }
        else if (!result)   // false
        {
            
        }
        else    // indeterminate
        {
            
        }
        
        // Continues read
        startAsynReadRequest(rcv_buffers_.back(), KEEPALIVE_TIMEOUT);
        cout << "KEEPALIVE_TIMEOUT" << endl;
}

void Connection::handleWriteRequest(const asio_error_code& err, 
                                    std::size_t bytes_transferred)
{
    
}

void Connection::setReadTimeout(int seconds)
{
    if (seconds != 0)
    {
        state_ |= Reading;
        //* change from seccond to milisecond
        readTimer_.expires_from_now(asio_timer_milliseconds(seconds));
        readTimer_.async_wait(boost::bind(&Connection::timeout,
                                        shared_from_this(),
                                        asio::placeholders::error));
    }
}

void Connection::setWriteTimeout(int seconds)
{
    state_ |= Writing;
    writeTimer_.expires_from_now(asio_timer_milliseconds(seconds));
    
    writeTimer_.async_wait(boost::bind(&Connection::timeout, 
                                    shared_from_this(), 
                                    asio::placeholders::error));
}

// *************************************************************************************
// Private Members
void Connection::handleError(const asio_error_code& err)
{
    close();
}


void Connection::cancelReadTimer()
{
    state_.clear(Reading);
    
    readTimer_.cancel();
}

void Connection::cancelWriteTimer()
{
    state_.clear(Writing);
    writeTimer_.cancel();
}


void Connection::timeout(const asio_error_code &err)
{
    cout << "Connection::timeout" << endl;
    if (err != asio::error::operation_aborted)
    {
        strand_.post(boost::bind(&Connection::doTimeout, shared_from_this()));
    }
}

void Connection::doTimeout()
{
    asio_error_code ignored_ec;
    socket().shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
    readTimer_.cancel();
    writeTimer_.cancel();
    
    cout << "Connection::doTimeout" << endl;
}

}   // namespace TcpServer
