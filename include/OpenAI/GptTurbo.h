#ifndef OpenAI_GptTurboH
#define OpenAI_GptTurboH

#include <queue>

#include "OpenAiModel.h"

namespace OpenAI
{
    enum class Role
    {
        System, User, Assistant
    };

    class GptTurbo : public OpenAiModel
    {
    private:
        static const std::string MODEL_NAME;
        static const unsigned char CONTEXT_SIZE;

        std::list<std::string> _context;

        std::string _user;
        std::string _name;
        std::string _role;

        float _temperature;
        float _top_p;
        unsigned char _n;
        std::int16_t _maxTokens;
        float _presence_penalty;
        float _frequency_penalty;

    public:
        typedef std::shared_ptr<GptTurbo> Ptr;

        explicit GptTurbo(const OpenAIApi::Ptr& api, const std::string& user = "",
                          const std::string& name = "", Role role = Role::User);
        ~GptTurbo() override = default;

        std::pair<std::string, int> Chat(const std::string& content);
    };
}

#endif