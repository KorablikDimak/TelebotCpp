#include "Common/HttpContext.h"

Common::HttpContext::HttpContext()
{
    Request = std::make_unique<HttpRequest>();
    Response = std::make_unique<HttpResponse>();
}
