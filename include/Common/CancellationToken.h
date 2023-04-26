#ifndef Common_CancellationTokenH
#define Common_CancellationTokenH

#include <atomic>

namespace Common
{
    class CancellationToken
    {
    private:
        std::atomic<bool*> _isCancellationRequested;

    public:
        explicit CancellationToken(bool* cancellationRequest);
        ~CancellationToken() = default;

        bool IsCancellationRequested() const;
    };
}

#endif