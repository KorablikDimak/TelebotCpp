#include <gtest/gtest.h>

#include "Telebot/HttpsClient.h"

TEST(HttpsClientTests, SendHttpsTest)
{
    const std::string host = "api.telegram.org";
    const std::string target = "/bot6123867817:AAEo3roQOmD-OCSWs1sB4zqdeHVM3WNMZIo/getme";

    std::shared_ptr<Telebot::HttpContext> httpContext = std::make_shared<Telebot::HttpContext>();
    httpContext->Request->method_string("GET");
    httpContext->Request->set(boost::beast::http::field::host, host);
    httpContext->Request->target(target);
    httpContext->Request->version(11);

    Telebot::HttpsClient client;
    client.SendHttps(httpContext);
}