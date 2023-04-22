#include "Telebot/Types/BotCommandScopeDefault.h"
#include "Telebot/Types/BotCommandScopeAllPrivateChats.h"
#include "Telebot/Types/BotCommandScopeAllGroupChats.h"
#include "Telebot/Types/BotCommandScopeAllChatAdministrators.h"
#include "Telebot/Types/BotCommandScopeChat.h"
#include "Telebot/Types/BotCommandScopeChatAdministrators.h"
#include "Telebot/Types/BotCommandScopeChatMember.h"

const std::string Telebot::BotCommandScopeDefault::TYPE = "default";
const std::string Telebot::BotCommandScopeAllPrivateChats::TYPE = "all_private_chats";
const std::string Telebot::BotCommandScopeAllGroupChats::TYPE = "all_group_chats";
const std::string Telebot::BotCommandScopeAllChatAdministrators::TYPE = "all_chat_administrators";
const std::string Telebot::BotCommandScopeChat::TYPE = "chat";
const std::string Telebot::BotCommandScopeChatAdministrators::TYPE = "chat_administrators";
const std::string Telebot::BotCommandScopeChatMember::TYPE = "chat_member";