#ifndef Telebot_HttpServerH
#define Telebot_HttpServerH

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>

#include "Configuration.h"
#include "HttpContext.h"

typedef boost::asio::io_service Service;
typedef boost::asio::ip::tcp::endpoint Endpoint;
typedef boost::asio::ip::address Address;
typedef boost::asio::ip::tcp::acceptor Acceptor;
typedef boost::asio::ip::tcp::socket Socket;
typedef std::map<std::string, std::string> ConfigDictionary;

namespace Telebot
{
    class HttpServer
    {
    private:
        std::unique_ptr<Service> _service;
        std::unique_ptr<Endpoint> _endpoint;
        std::unique_ptr<Acceptor> _acceptor;

        std::string _serverIP;
        std::size_t _bufferSize;

    public:
        explicit HttpServer(Configuration* configuration);
        ~HttpServer() = default;

        void Start();
        void Stop();

        void HandleConnections();
        void Read(const std::shared_ptr<HttpContext>& context);
    };
}

#endif