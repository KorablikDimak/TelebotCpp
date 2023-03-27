#ifndef Telebot_WebhookInfoH
#define Telebot_WebhookInfoH

#include <memory>
#include <string>
#include <vector>

namespace Telebot
{
    class WebhookInfo
    {
    public:
        typedef std::shared_ptr<WebhookInfo> Ptr;

        std::string Url;
        bool HasCustomCertificate;
        std::int32_t PendingUpdateCount;
        std::string IpAddress;
        std::int32_t LastErrorDate;
        std::string LastErrorMessage;
        std::int32_t LastSynchronizationErrorDate;
        std::int32_t MaxConnections;
        std::vector<std::string> AllowedUpdates;
    };
}

#endif