#ifndef Telebot_HttpContextH
#define Telebot_HttpContextH

#include <memory>

#include "HttpRequest.h"
#include "HttpResponse.h"

namespace Telebot
{
    class HttpContext
    {
    public:
        HttpContext();
        ~HttpContext() = default;

        std::unique_ptr<HttpRequest> Request;
        std::unique_ptr<HttpResponse> Response;
    };
}

#endif