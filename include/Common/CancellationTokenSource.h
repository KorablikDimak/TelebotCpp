#ifndef Common_CancellationTokenSourceH
#define Common_CancellationTokenSourceH

#include "CancellationToken.h"

namespace Common
{
    class CancellationTokenSource
    {
    private:
        std::atomic<bool*> _cancellationRequest;
        CancellationToken* _token;

    public:
        CancellationTokenSource();
        ~CancellationTokenSource();

        CancellationToken* Token() const;
        void Cancel();
    };
}

#endif