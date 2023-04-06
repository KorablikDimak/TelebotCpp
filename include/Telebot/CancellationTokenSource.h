#ifndef Telebot_CancellationTokenSourceH
#define Telebot_CancellationTokenSourceH

#include "CancellationToken.h"

namespace Telebot
{
    class CancellationTokenSource
    {
    private:
        bool* _cancellationRequest;
        CancellationToken* _token;

    public:
        CancellationTokenSource();
        ~CancellationTokenSource();

        CancellationToken* Token() const;
        void Cancel();
    };
}

#endif