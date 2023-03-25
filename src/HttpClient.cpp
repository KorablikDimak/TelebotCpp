#include "Telebot/HttpClient.h"

Telebot::HttpClient::HttpClient(Service* service)
{
    _socket = std::make_unique<Socket>(*service);
}

void Telebot::HttpClient::Write(const std::shared_ptr<HttpContext>& context)
{

}