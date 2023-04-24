#ifndef OpenAI_GptTurboH
#define OpenAI_GptTurboH

#include "GptModel.h"

namespace OpenAI
{
    enum class Role
    {
        System, User, Assistant
    };

    class GptTurbo : public GptModel
    {
    private:
        std::string _role;
        std::string _name;
        std::string _user;

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

        std::string Chat(const std::string& content) override;
    };
}

#endif