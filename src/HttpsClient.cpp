#include "Telebot/HttpsClient.h"

Telebot::HttpsClient::HttpsClient()
{
    _service = std::make_unique<Service>();
    SslContext sslContext(SslContext::sslv23_client);
    _sslSocket = std::make_unique<SslSocket>(*_service, sslContext);
}

void Telebot::HttpsClient::SendHttps(const std::shared_ptr<HttpContext>& context)
{
    Resolver resolver(*_service);
    auto ip = resolver.resolve((*context->Request)[boost::beast::http::field::host], HTTPS_PORT);
    boost::asio::connect(_sslSocket->lowest_layer(), ip);
    _sslSocket->handshake(boost::asio::ssl::stream_base::handshake_type::client);

    boost::beast::http::write(*_sslSocket, *context->Request);
    boost::beast::flat_buffer buffer;
    boost::beast::http::read(*_sslSocket, buffer, *context->Response);
}