#include "Telebot/HttpServer.h"

Telebot::HttpServer::HttpServer(Configuration* configuration)
{
    ConfigDictionary* config = configuration->GetConfig();
    _serverIP = (*config)["serverip"];
    _bufferSize = std::stoi((*config)["serverbuffersize"]);

    _service = std::make_unique<Service>();
}

void Telebot::HttpServer::Start()
{
    _service->run();
}

void Telebot::HttpServer::Stop()
{
    _service->stop();
}

void Telebot::HttpServer::HandleConnections()
{

}

void Telebot::HttpServer::Read(const std::shared_ptr<HttpContext>& context)
{

}