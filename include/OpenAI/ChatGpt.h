#ifndef OpenAI_ChatGptH
#define OpenAI_ChatGptH

#include "OpenAIApi.h"

namespace OpenAI
{
    class ChatGpt
    {
    private:
        static const std::string MODEL;
        static const unsigned char N;
        static const std::int16_t MAX_TOKENS;

        OpenAIApi::Ptr _api;
        std::string _name;
        std::string _user;

        std::string _role;
        float _temperature;
        float _top_p;
        float _presence_penalty;
        float _frequency_penalty;

    public:
        typedef std::shared_ptr<ChatGpt> Ptr;

        ChatGpt(const OpenAIApi::Ptr& api, const std::string& name, const std::string& user = "");
        ~ChatGpt() = default;

        std::string Chat(const std::string& content);
    };
}

#endif