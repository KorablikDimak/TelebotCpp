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
    public:
        HttpsClient() = default;
        ~HttpsClient() = default;

        template <typename RequestBody, typename ResponseBody>
        static void SendHttpsAsync(const std::shared_ptr<HttpContext<RequestBody, ResponseBody>>& context, bool useSNI = false)
        {
            Service service;
            Service::work work(service);
            std::thread thread([&service](){ service.run(); });

            SslContext sslContext(SslContext::tlsv13_client);
            SslSocket sslSocket(service, sslContext);

            if (useSNI)
            {
                SSL_set_tlsext_host_name(sslSocket.native_handle(), (*context->Request)[boost::beast::http::field::host].to_string().c_str());
                sslSocket.set_verify_callback(boost::asio::ssl::host_name_verification((*context->Request)[boost::beast::http::field::host].to_string()));
            }

            Resolver resolver(service);
            auto ip = resolver.resolve((*context->Request)[boost::beast::http::field::host], "443");

            auto onConnect = boost::asio::async_connect(sslSocket.lowest_layer(), ip, boost::asio::use_future);
            onConnect.get();

            auto onHandshake = sslSocket.async_handshake(boost::asio::ssl::stream_base::client, boost::asio::use_future);
            onHandshake.get();

            auto onWrite = boost::beast::http::async_write(sslSocket, *context->Request, boost::asio::use_future);
            onWrite.get();

            boost::beast::flat_buffer buffer;
            while (!context->Response->is_done())
            {
                auto onRead = boost::beast::http::async_read_some(sslSocket, buffer, *context->Response, boost::asio::use_future);
                onRead.get();
            }

            service.stop();
            thread.join();
        }
    };
}

#endif