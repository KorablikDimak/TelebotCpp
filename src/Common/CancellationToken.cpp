#include "Common/CancellationToken.h"

Common::CancellationToken::CancellationToken(bool* cancellationRequest)
{
    _isCancellationRequested = cancellationRequest;
}

bool Common::CancellationToken::IsCancellationRequested() const
{
    return *_isCancellationRequested;
}