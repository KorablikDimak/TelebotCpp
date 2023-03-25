#include "Telebot/Types/ChatMemberOwner.h"
#include "Telebot/Types/ChatMemberAdministrator.h"
#include "Telebot/Types/ChatMemberMember.h"
#include "Telebot/Types/ChatMemberRestricted.h"
#include "Telebot/Types/ChatMemberLeft.h"
#include "Telebot/Types/ChatMemberBanned.h"

const std::string Telebot::ChatMemberOwner::STATUS = "creator";
const std::string Telebot::ChatMemberAdministrator::STATUS = "administrator";
const std::string Telebot::ChatMemberMember::STATUS = "member";
const std::string Telebot::ChatMemberRestricted::STATUS = "restricted";
const std::string Telebot::ChatMemberLeft::STATUS = "left";
const std::string Telebot::ChatMemberBanned::STATUS = "kicked";