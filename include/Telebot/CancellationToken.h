#ifndef Telebot_CancellationTokenH
#define Telebot_CancellationTokenH

namespace Telebot
{
    class CancellationToken
    {
    private:
        bool* _isCancellationRequested;

    public:
        explicit CancellationToken(bool* cancellationRequest);
        ~CancellationToken() = default;

        bool IsCancellationRequested() const;
    };
}

#endif