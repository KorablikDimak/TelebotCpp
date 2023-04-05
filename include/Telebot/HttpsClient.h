#ifndef Telebot_HttpClientH
#define Telebot_HttpClientH

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/core/flat_buffer.hpp>

#include "HttpContext.h"

typedef boost::asio::io_service Service;
typedef boost::asio::ssl::context SslContext;
typedef boost::asio::ip::tcp::socket Socket;
typedef boost::asio::ssl::stream<Socket> SslSocket;
typedef boost::asio::ip::tcp::resolver Resolver;

namespace Telebot
{
    class HttpsClient
    {
    private:
        std::unique_ptr<Service> _service;
        std::unique_ptr<SslSocket> _sslSocket;

        static const std::string HTTPS_PORT;

    public:
        HttpsClient();
        ~HttpsClient() = default;

        void SendHttps(const std::shared_ptr<HttpContext>& context);
    };
}

#endif