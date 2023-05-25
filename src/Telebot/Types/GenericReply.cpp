#include "Telebot/Types/InlineKeyboardMarkup.h"
#include "Telebot/Types/ForceReply.h"
#include "Telebot/Types/ReplyKeyboardMarkup.h"
#include "Telebot/Types/ReplyKeyboardRemove.h"

void Telebot::InlineKeyboardMarkup::SetButton(const InlineKeyboardButton::Ptr& button, unsigned char row, unsigned char column)
{
    if (inline_keyboard.size() <= row)
        inline_keyboard.resize(row + 1);
    if (inline_keyboard[row].size() <= column)
        inline_keyboard[row].resize(column + 1);

    inline_keyboard[row][column] = button;
}

void Telebot::InlineKeyboardMarkup::RemoveButton(unsigned char row, unsigned char column)
{
    if (inline_keyboard.size() <= row) return;
    if (inline_keyboard[row].size() <= column) return;
    inline_keyboard[row].erase(inline_keyboard[row].begin() + column);
}

void Telebot::GenericReply::ToJson(Json& json, const GenericReply::Ptr& object) {}

void Telebot::InlineKeyboardMarkup::ToJson(Json& json, const GenericReply::Ptr& object)
{
    std::shared_ptr<InlineKeyboardMarkup> inlineKeyboardMarkup = std::dynamic_pointer_cast<InlineKeyboardMarkup>(object);
    if (inlineKeyboardMarkup != nullptr)
        to_json(json, inlineKeyboardMarkup);
}

void Telebot::ForceReply::ToJson(Json& json, const GenericReply::Ptr& object)
{
    std::shared_ptr<ForceReply> forceReply = std::dynamic_pointer_cast<ForceReply>(object);
    if (forceReply != nullptr)
        to_json(json, forceReply);
}

void Telebot::ReplyKeyboardMarkup::ToJson(Json& json, const GenericReply::Ptr& object)
{
    std::shared_ptr<ReplyKeyboardMarkup> replyKeyboardMarkup = std::dynamic_pointer_cast<ReplyKeyboardMarkup>(object);
    if (replyKeyboardMarkup != nullptr)
        to_json(json, replyKeyboardMarkup);
}

void Telebot::ReplyKeyboardRemove::ToJson(Json& json, const GenericReply::Ptr& object)
{
    std::shared_ptr<ReplyKeyboardRemove> replyKeyboardRemove = std::dynamic_pointer_cast<ReplyKeyboardRemove>(object);
    if (replyKeyboardRemove != nullptr)
        to_json(json, replyKeyboardRemove);
}