#ifndef Telebot_UpdateH
#define Telebot_UpdateH

#include "Telebot/Types/Message.h"
#include "Telebot/Types/InlineQuery.h"
#include "Telebot/Types/ChosenInlineResult.h"
#include "Telebot/Types/CallbackQuery.h"
#include "Telebot/Types/ShippingQuery.h"
#include "Telebot/Types/PreCheckoutQuery.h"
#include "Telebot/Types/Poll.h"
#include "Telebot/Types/PollAnswer.h"
#include "Telebot/Types/ChatMemberUpdated.h"
#include "Telebot/Types/ChatJoinRequest.h"

namespace Telebot
{
    class Update
    {
    public:
        typedef std::shared_ptr<Update> Ptr;

        int UpdateId;
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