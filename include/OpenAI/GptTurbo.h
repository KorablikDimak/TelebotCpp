#ifndef OpenAI_GptTurboH
#define OpenAI_GptTurboH

#include <queue>

#include "OpenAIModel.h"

namespace OpenAI
{
    enum class Role
    {
        System = 0,
        User = 1,
        Assistant = 2
    };

    inline std::string ToString(Role role)
    {
        switch (role)
        {
            case Role::System:
                return "system";
            case Role::User:
                return "user";
            case Role::Assistant:
                return "assistant";
        }
    }

    class GptTurbo : public OpenAIModel
    {
    private:
        static const std::string MODEL_NAME;

        static const float TOP_P;
        static const unsigned char N;
        static const std::int16_t MAX_TOKENS;
        static const float PRESENCE_PENALTY;
        static const float FREQUENCY_PENALTY;

        std::string _user;
        std::string _name;

        unsigned char _contextSize;
        float _temperature;

        std::list<std::pair<Role, std::string>> _context;
        bool _allowModelMessagesInContext;

    public:
        typedef std::shared_ptr<GptTurbo> Ptr;

        explicit GptTurbo(const OpenAIApi::Ptr& api, const std::string& user = "", const std::string& name = "");
        ~GptTurbo() override = default;

        std::pair<std::string, int> Chat(const std::string& content);

        void AddSystemMessage(const std::string& content);

        void SetContextSize(unsigned char contextSize);
        void SetTemperature(float temperature);
        void AllowModelMessagesInContext(bool allow);
    };
}

#endif