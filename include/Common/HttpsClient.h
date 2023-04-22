#ifndef Common_HttpsClientH
#define Common_HttpsClientH

#include <future>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/core/flat_buffer.hpp>

#include "HttpContext.h"

typedef boost::asio::io_service Service;
typedef boost::asio::ssl::context SslContext;
typedef boost::asio::ip::tcp::socket Socket;
typedef boost::asio::ssl::stream<Socket> SslSocket;
typedef boost::asio::ip::tcp::resolver Resolver;

namespace Common
{
    class HttpsClient
    {
    private:
        static const std::string HTTPS_PORT;

    public:
        HttpsClient() = default;
        ~HttpsClient() = default;

        static void SendHttpsAsync(const HttpContext::Ptr& context);
    };
}

#endif