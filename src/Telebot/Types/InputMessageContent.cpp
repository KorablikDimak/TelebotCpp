#include "Telebot/Types/InputTextMessageContent.h"
#include "Telebot/Types/InputLocationMessageContent.h"
#include "Telebot/Types/InputVenueMessageContent.h"
#include "Telebot/Types/InputContactMessageContent.h"
#include "Telebot/Types/InputInvoiceMessageContent.h"

const std::string Telebot::InputTextMessageContent::TYPE = "text";
const std::string Telebot::InputLocationMessageContent::TYPE = "location";
const std::string Telebot::InputVenueMessageContent::TYPE = "venue";
const std::string Telebot::InputContactMessageContent::TYPE = "contact";
const std::string Telebot::InputInvoiceMessageContent::TYPE = "invoice";