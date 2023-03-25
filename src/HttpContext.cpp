#include "Telebot/HttpContext.h"

Telebot::HttpContext::HttpContext()
{
    Request = std::make_unique<HttpRequest>();
    Response = std::make_unique<HttpResponse>();
}
