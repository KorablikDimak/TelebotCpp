#ifndef Common_CancellationTokenH
#define Common_CancellationTokenH

namespace Common
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