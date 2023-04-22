#include "Common/CancellationTokenSource.h"

Common::CancellationTokenSource::CancellationTokenSource()
{
    _cancellationRequest = new bool(false);
    _token = new CancellationToken(_cancellationRequest);
}

Common::CancellationTokenSource::~CancellationTokenSource()
{
    delete _cancellationRequest;
    delete _token;
}

Common::CancellationToken* Common::CancellationTokenSource::Token() const
{
    return _token;
}

void Common::CancellationTokenSource::Cancel()
{
    *_cancellationRequest = true;
}