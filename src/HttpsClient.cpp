#include "Telebot/HttpsClient.h"

const std::string Telebot::HttpsClient::HTTPS_PORT = "443";

void Telebot::HttpsClient::SendHttpsAsync(const std::shared_ptr<HttpContext>& context)
{
    boost::asio::io_service service;
    Service::work work(service);
    std::thread thread([&service](){ service.run(); });

    SslContext sslContext(SslContext::sslv23_client);
    std::shared_ptr<SslSocket> sslSocket = std::make_shared<SslSocket>(service, sslContext);
    Resolver resolver(service);
    auto ip = resolver.resolve((*context->Request)[boost::beast::http::field::host], HTTPS_PORT);

    auto onConnect = boost::asio::async_connect(sslSocket->lowest_layer(), ip, boost::asio::use_future);
    onConnect.get();

    auto onHandshake = sslSocket->async_handshake(boost::asio::ssl::stream_base::handshake_type::client,
                                                  boost::asio::use_future);
    onHandshake.get();

    auto onWrite = boost::beast::http::async_write(*sslSocket, *context->Request, boost::asio::use_future);
    onWrite.get();

    boost::beast::flat_buffer buffer;
    while (!context->Response->is_done())
    {
        auto onRead = boost::beast::http::async_read_some(*sslSocket, buffer, *context->Response,
                                                               boost::asio::use_future);
        onRead.get();
    }

    service.stop();
    thread.join();
}