#ifndef Telebot_HttpClientH
#define Telebot_HttpClientH

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>

#include "HttpContext.h"

typedef boost::asio::io_service Service;
typedef boost::asio::ip::tcp::endpoint Endpoint;
typedef boost::asio::ip::address Address;
typedef boost::asio::ip::tcp::socket Socket;

namespace Telebot
{
    class HttpClient
    {
    private:
        std::unique_ptr<Endpoint> _endpoint;
        std::unique_ptr<Socket> _socket;

    public:
        explicit HttpClient(Service* service);
        ~HttpClient() = default;

        void Write(const std::shared_ptr<HttpContext>& context);
    };
}

#endif