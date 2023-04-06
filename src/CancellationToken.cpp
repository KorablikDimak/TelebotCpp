#include "Telebot/CancellationToken.h"

Telebot::CancellationToken::CancellationToken(bool* cancellationRequest)
{
    _isCancellationRequested = cancellationRequest;
}

bool Telebot::CancellationToken::IsCancellationRequested() const
{
    return *_isCancellationRequested;
}