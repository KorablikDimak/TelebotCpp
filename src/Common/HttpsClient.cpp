#include "Common/HttpsClient.h"

const std::string Common::HttpsClient::HTTPS_PORT = "443";

void Common::HttpsClient::SendHttpsAsync(const HttpContext::Ptr& context, bool useSNI)
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
    auto ip = resolver.resolve((*context->Request)[boost::beast::http::field::host], HTTPS_PORT);

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