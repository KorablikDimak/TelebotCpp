#include "Telebot/CancellationTokenSource.h"

Telebot::CancellationTokenSource::CancellationTokenSource()
{
    _cancellationRequest = new bool(false);
    _token = new CancellationToken(_cancellationRequest);
}

Telebot::CancellationTokenSource::~CancellationTokenSource()
{
    delete _cancellationRequest;
    delete _token;
}

Telebot::CancellationToken* Telebot::CancellationTokenSource::Token() const
{
    return _token;
}

void Telebot::CancellationTokenSource::Cancel()
{
    *_cancellationRequest = true;
}