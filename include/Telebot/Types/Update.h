#ifndef Telebot_UpdateH
#define Telebot_UpdateH

#include "Message.h"
#include "InlineQuery.h"
#include "ChosenInlineResult.h"
#include "CallbackQuery.h"
#include "ShippingQuery.h"
#include "PreCheckoutQuery.h"
#include "Poll.h"
#include "PollAnswer.h"
#include "ChatMemberUpdated.h"
#include "ChatJoinRequest.h"

namespace Telebot
{
    class Update
    {
    public:
        typedef std::shared_ptr<Update> Ptr;

        std::int32_t UpdateId;
        Message::Ptr Message;
        Message::Ptr EditedMessage;
        Message::Ptr ChannelPost;
        Message::Ptr EditedChannelPost;
        InlineQuery::Ptr InlineQuery;
        ChosenInlineResult::Ptr ChosenInlineResult;
        CallbackQuery::Ptr CallbackQuery;
        ShippingQuery::Ptr ShippingQuery;
        PreCheckoutQuery::Ptr PreCheckoutQuery;
        Poll::Ptr Poll;
        PollAnswer::Ptr PollAnswer;
        ChatMemberUpdated::Ptr MyChatMember;
        ChatMemberUpdated::Ptr ChatMember;
        ChatJoinRequest::Ptr ChatJoinRequest;
    };
}

#endif