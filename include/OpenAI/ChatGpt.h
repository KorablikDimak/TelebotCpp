#ifndef OpenAI_ChatGptH
#define OpenAI_ChatGptH

#include "OpenAIApi.h"

namespace OpenAI
{
    class ChatGpt
    {
    private:
        OpenAIApi::Ptr _api;
        std::string _name;

        static const std::string MODEL;
        static const std::int16_t MAX_TOKENS;

    public:
        typedef std::shared_ptr<ChatGpt> Ptr;

        ChatGpt(const OpenAIApi::Ptr& token, const std::string& name);
        ~ChatGpt() = default;
    };
}

#endif