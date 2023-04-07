#include "Telebot/Api.h"

const std::string Telebot::Api::HOST = "api.telegram.org";
const unsigned int Telebot::Api::HTTP_VERSION = 11;

Telebot::Api::Api(const std::string& token)
{
    _token = token;
    _client = std::make_unique<HttpsClient>();
}

Json Telebot::Api::Get(const std::string& methodName)
{
    std::shared_ptr<Telebot::HttpContext> httpContext = std::make_shared<Telebot::HttpContext>();
    httpContext->Request->method_string("GET");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/bot" + _token + "/" + methodName);
    httpContext->Request->version(HTTP_VERSION);

    _client->SendHttps(httpContext);
    Json json = Json::parse(httpContext->Response->body());
    if (json.at("ok").get<bool>()) return json.at("result");
}

Json Telebot::Api::Post(const std::string& methodName, const Json& params)
{
    std::shared_ptr<Telebot::HttpContext> httpContext = std::make_shared<Telebot::HttpContext>();
    httpContext->Request->method_string("POST");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/bot" + _token + "/" + methodName);
    httpContext->Request->version(HTTP_VERSION);
    httpContext->Request->body() = params.dump();

    _client->SendHttps(httpContext);

    Json json = Json::parse(httpContext->Response->body());
    if (json.at("ok").get<bool>()) return json.at("result");
}

std::vector<Telebot::Update::Ptr> Telebot::Api::GetUpdates(int offset,
                                                           int limit,
                                                           int timeout,
                                                           const std::vector<std::string>& allowedUpdates)
{
    Json requestBody;
    requestBody["offset"] = offset;
    requestBody["limit"] = limit;
    requestBody["timeout"] = timeout;
    requestBody["allowed_updates"] = allowedUpdates;
    Json responseBody = Post("getUpdates", requestBody);

    std::vector<Update::Ptr> result;
    for (const Json& element : responseBody)
    {
        Update::Ptr update = std::make_shared<Update>();
        *update = element.get<Update>();
        result.push_back(update);
    }
    return result;
}

bool Telebot::Api::SetWebhook(const std::string &url,
                              const InputFile::Ptr& certificate,
                              std::int32_t maxConnections,
                              const std::vector<std::string> &allowedUpdates,
                              const std::string &ipAddress,
                              bool dropPendingUpdates,
                              const std::string &secretToken)
{

}

bool Telebot::Api::DeleteWebhook(bool dropPendingUpdates)
{

}

Telebot::WebhookInfo::Ptr Telebot::Api::GetWebhookInfo()
{

}

Telebot::User::Ptr Telebot::Api::GetMe()
{
    Json responseBody = Get("getMe");
    User::Ptr user = std::make_shared<User>();
    *user = responseBody.get<User>();
    return user;
}

bool Telebot::Api::LogOut()
{

}

bool Telebot::Api::Close()
{

}

Telebot::Message::Ptr Telebot::Api::SendMessage(const boost::variant<std::int64_t, std::string>& chatId,
                                                const std::string& text,
                                                bool disableWebPagePreview,
                                                std::int32_t replyToMessageId,
                                                const Telebot::GenericReply::Ptr& replyMarkup,
                                                const std::string& parseMode,
                                                bool disableNotification,
                                                const std::vector<MessageEntity::Ptr>& entities,
                                                bool allowSendingWithoutReply,
                                                bool protectContent,
                                                std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::ForwardMessage(const boost::variant<std::int64_t, std::string>& chatId,
                                                   const boost::variant<std::int64_t, std::string>& fromChatId,
                                                   std::int32_t messageId,
                                                   bool disableNotification,
                                                   bool protectContent,
                                                   std::int32_t messageThreadId)
{

}

Telebot::MessageId::Ptr Telebot::Api::CopyMessage(const boost::variant<std::int64_t, std::string>& chatId,
                                                  const boost::variant<std::int64_t, std::string>& fromChatId,
                                                  std::int32_t messageId,
                                                  const std::string& caption,
                                                  const std::string& parseMode,
                                                  const std::vector<MessageEntity::Ptr>& captionEntities,
                                                  bool disableNotification,
                                                  std::int32_t replyToMessageId,
                                                  bool allowSendingWithoutReply,
                                                  const GenericReply::Ptr& replyMarkup,
                                                  bool protectContent,
                                                  std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendPhoto(const boost::variant<std::int64_t, std::string>& chatId,
                                              const boost::variant<InputFile::Ptr, std::string>& photo,
                                              const std::string& caption,
                                              std::int32_t replyToMessageId,
                                              const Telebot::GenericReply::Ptr& replyMarkup,
                                              const std::string& parseMode,
                                              bool disableNotification,
                                              const std::vector<MessageEntity::Ptr>& captionEntities,
                                              bool allowSendingWithoutReply,
                                              bool protectContent,
                                              std::int32_t messageThreadId,
                                              bool hasSpoiler)
{

}

Telebot::Message::Ptr Telebot::Api::SendAudio(const boost::variant<std::int64_t, std::string>& chatId,
                                              const boost::variant<InputFile::Ptr, std::string>& audio,
                                              const std::string& caption,
                                              std::int32_t duration,
                                              const std::string& performer,
                                              const std::string& title,
                                              const boost::variant<InputFile::Ptr, std::string>& thumb,
                                              std::int32_t replyToMessageId,
                                              const Telebot::GenericReply::Ptr& replyMarkup,
                                              const std::string& parseMode,
                                              bool disableNotification,
                                              const std::vector<MessageEntity::Ptr>& captionEntities,
                                              bool allowSendingWithoutReply,
                                              bool protectContent,
                                              std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendDocument(const boost::variant<std::int64_t, std::string>& chatId,
                                                 const boost::variant<InputFile::Ptr, std::string>& document,
                                                 const boost::variant<InputFile::Ptr, std::string>& thumb,
                                                 const std::string& caption,
                                                 std::int32_t replyToMessageId,
                                                 const Telebot::GenericReply::Ptr& replyMarkup,
                                                 const std::string& parseMode,
                                                 bool disableNotification,
                                                 const std::vector<MessageEntity::Ptr>& captionEntities,
                                                 bool disableContentTypeDetection,
                                                 bool allowSendingWithoutReply,
                                                 bool protectContent,
                                                 std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendVideo(const boost::variant<std::int64_t, std::string>& chatId,
                                              const boost::variant<InputFile::Ptr, std::string>& video,
                                              bool supportsStreaming,
                                              std::int32_t duration,
                                              std::int32_t width,
                                              std::int32_t height,
                                              const boost::variant<InputFile::Ptr, std::string>& thumb,
                                              const std::string &caption,
                                              std::int32_t replyToMessageId,
                                              const Telebot::GenericReply::Ptr& replyMarkup,
                                              const std::string &parseMode,
                                              bool disableNotification,
                                              const std::vector<MessageEntity::Ptr>& captionEntities,
                                              bool allowSendingWithoutReply,
                                              bool protectContent,
                                              std::int32_t messageThreadId,
                                              bool hasSpoiler)
{

}

Telebot::Message::Ptr Telebot::Api::SendAnimation(const boost::variant<std::int64_t, std::string>& chatId,
                                                  const boost::variant<InputFile::Ptr, std::string>& animation,
                                                  std::int32_t duration,
                                                  std::int32_t width,
                                                  std::int32_t height,
                                                  const boost::variant<InputFile::Ptr, std::string>& thumb,
                                                  const std::string& caption,
                                                  std::int32_t replyToMessageId,
                                                  const Telebot::GenericReply::Ptr& replyMarkup,
                                                  const std::string &parseMode,
                                                  bool disableNotification,
                                                  const std::vector<MessageEntity::Ptr>& captionEntities,
                                                  bool allowSendingWithoutReply,
                                                  bool protectContent,
                                                  std::int32_t messageThreadId,
                                                  bool hasSpoiler)
{

}

Telebot::Message::Ptr Telebot::Api::SendVoice(const boost::variant<std::int64_t, std::string>& chatId,
                                              const boost::variant<InputFile::Ptr, std::string>& voice,
                                              const std::string &caption,
                                              std::int32_t duration,
                                              std::int32_t replyToMessageId,
                                              const Telebot::GenericReply::Ptr& replyMarkup,
                                              const std::string& parseMode,
                                              bool disableNotification,
                                              const std::vector<MessageEntity::Ptr>& captionEntities,
                                              bool allowSendingWithoutReply,
                                              bool protectContent,
                                              std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendVideoNote(const boost::variant<std::int64_t, std::string>& chatId,
                                                  const boost::variant<InputFile::Ptr, std::string>& videoNote,
                                                  std::int64_t replyToMessageId,
                                                  bool disableNotification,
                                                  std::int32_t duration,
                                                  std::int32_t length,
                                                  const boost::variant<InputFile::Ptr, std::string>& thumb,
                                                  const Telebot::GenericReply::Ptr& replyMarkup,
                                                  bool allowSendingWithoutReply,
                                                  bool protectContent,
                                                  std::int32_t messageThreadId)
{

}

std::vector<Telebot::Message::Ptr> Telebot::Api::SendMediaGroup(const boost::variant<std::int64_t, std::string>& chatId,
                                                                const std::vector<InputMedia::Ptr>& media,
                                                                bool disableNotification,
                                                                std::int32_t replyToMessageId,
                                                                bool allowSendingWithoutReply,
                                                                bool protectContent,
                                                                std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendLocation(const boost::variant<std::int64_t, std::string>& chatId,
                                                 float latitude,
                                                 float longitude,
                                                 std::int32_t livePeriod,
                                                 std::int32_t replyToMessageId,
                                                 const Telebot::GenericReply::Ptr& replyMarkup,
                                                 bool disableNotification,
                                                 float horizontalAccuracy,
                                                 std::int32_t heading,
                                                 std::int32_t proximityAlertRadius,
                                                 bool allowSendingWithoutReply,
                                                 bool protectContent,
                                                 std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendVenue(const boost::variant<std::int64_t, std::string>& chatId,
                                              float latitude,
                                              float longitude,
                                              const std::string& title,
                                              const std::string& address,
                                              const std::string& foursquareId,
                                              const std::string& foursquareType,
                                              bool disableNotification,
                                              std::int32_t replyToMessageId,
                                              const Telebot::GenericReply::Ptr& replyMarkup,
                                              const std::string& googlePlaceId,
                                              const std::string& googlePlaceType,
                                              bool allowSendingWithoutReply,
                                              bool protectContent,
                                              std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendContact(const boost::variant<std::int64_t, std::string>& chatId,
                                                const std::string& phoneNumber,
                                                const std::string& firstName,
                                                const std::string& lastName,
                                                const std::string& vcard,
                                                bool disableNotification,
                                                std::int32_t replyToMessageId,
                                                const Telebot::GenericReply::Ptr& replyMarkup,
                                                bool allowSendingWithoutReply,
                                                bool protectContent,
                                                std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendPoll(const boost::variant<std::int64_t, std::string>& chatId,
                                             const std::string& question,
                                             const std::vector<std::string>& options,
                                             bool disableNotification,
                                             std::int32_t replyToMessageId,
                                             const Telebot::GenericReply::Ptr& replyMarkup,
                                             bool isAnonymous,
                                             const std::string& type,
                                             bool allowsMultipleAnswers,
                                             std::int32_t correctOptionId,
                                             const std::string& explanation,
                                             const std::string& explanationParseMode,
                                             const std::vector<MessageEntity::Ptr>& explanationEntities,
                                             std::int32_t openPeriod,
                                             std::int32_t closeDate,
                                             bool isClosed,
                                             bool allowSendingWithoutReply,
                                             bool protectContent,
                                             std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendDice(const boost::variant<std::int64_t, std::string>& chatId,
                                             bool disableNotification,
                                             std::int32_t replyToMessageId,
                                             const Telebot::GenericReply::Ptr& replyMarkup,
                                             const std::string& emoji,
                                             bool allowSendingWithoutReply,
                                             bool protectContent,
                                             std::int32_t messageThreadId)
{

}

bool Telebot::Api::SendChatAction(std::int64_t chatId,
                                  const std::string& action,
                                  std::int32_t messageThreadId)
{

}

Telebot::UserProfilePhotos::Ptr Telebot::Api::GetUserProfilePhotos(std::int64_t userId,
                                                                   std::int32_t offset,
                                                                   std::int32_t limit)
{

}

Telebot::File::Ptr Telebot::Api::GetFile(const std::string& fileId)
{

}

bool Telebot::Api::BanChatMember(const boost::variant<std::int64_t, std::string>& chatId,
                                 std::int64_t userId,
                                 std::int32_t untilDate,
                                 bool revokeMessages)
{

}

bool Telebot::Api::UnbanChatMember(const boost::variant<std::int64_t, std::string>& chatId,
                                   std::int64_t userId,
                                   bool onlyIfBanned)
{

}

bool Telebot::Api::RestrictChatMember(const boost::variant<std::int64_t, std::string>& chatId,
                                      std::int64_t userId,
                                      const Telebot::ChatPermissions::Ptr& permissions,
                                      std::int64_t untilDate,
                                      bool useIndependentChatPermissions)
{

}

bool Telebot::Api::PromoteChatMember(const boost::variant<std::int64_t, std::string>& chatId,
                                     std::int64_t userId,
                                     bool canChangeInfo,
                                     bool canPostMessages,
                                     bool canEditMessages,
                                     bool canDeleteMessages,
                                     bool canInviteUsers,
                                     bool canPinMessages,
                                     bool canPromoteMembers,
                                     bool isAnonymous,
                                     bool canManageChat,
                                     bool canManageVideoChats,
                                     bool canRestrictMembers,
                                     bool canManageTopics)
{

}

bool Telebot::Api::SetChatAdministratorCustomTitle(const boost::variant<std::int64_t, std::string>& chatId,
                                                   std::int64_t userId,
                                                   const std::string& customTitle)
{

}

bool Telebot::Api::BanChatSenderChat(const boost::variant<std::int64_t, std::string>& chatId,
                                     std::int64_t senderChatId)
{

}

bool Telebot::Api::UnbanChatSenderChat(const boost::variant<std::int64_t, std::string>& chatId,
                                       std::int64_t senderChatId)
{

}

bool Telebot::Api::SetChatPermissions(const boost::variant<std::int64_t, std::string>& chatId,
                                      const Telebot::ChatPermissions::Ptr& permissions,
                                      bool useIndependentChatPermissions)
{

}

std::string Telebot::Api::ExportChatInviteLink(const boost::variant<std::int64_t, std::string>& chatId)
{

}

Telebot::ChatInviteLink::Ptr Telebot::Api::CreateChatInviteLink(const boost::variant<std::int64_t, std::string>& chatId,
                                                                std::int32_t expireDate,
                                                                std::int32_t memberLimit,
                                                                const std::string& name,
                                                                bool createsJoinRequest)
{

}

Telebot::ChatInviteLink::Ptr Telebot::Api::EditChatInviteLink(const boost::variant<std::int64_t, std::string>& chatId,
                                                              const std::string& inviteLink,
                                                              std::int32_t expireDate,
                                                              std::int32_t memberLimit,
                                                              const std::string& name,
                                                              bool createsJoinRequest)
{

}

Telebot::ChatInviteLink::Ptr Telebot::Api::RevokeChatInviteLink(const boost::variant<std::int64_t, std::string>& chatId,
                                                                const std::string& inviteLink)
{

}

bool Telebot::Api::ApproveChatJoinRequest(const boost::variant<std::int64_t, std::string>& chatId,
                                          std::int64_t userId)
{

}

bool Telebot::Api::DeclineChatJoinRequest(const boost::variant<std::int64_t, std::string>& chatId,
                                          std::int64_t userId)
{

}

bool Telebot::Api::SetChatPhoto(const boost::variant<std::int64_t, std::string>& chatId,
                                const InputFile::Ptr& photo)
{

}

bool Telebot::Api::DeleteChatPhoto(const boost::variant<std::int64_t, std::string>& chatId)
{

}

bool Telebot::Api::SetChatTitle(const boost::variant<std::int64_t, std::string>& chatId,
                                const std::string& title)
{

}

bool Telebot::Api::SetChatDescription(const boost::variant<std::int64_t,
                                      std::string>& chatId,
                                      const std::string& description)
{

}

bool Telebot::Api::PinChatMessage(const boost::variant<std::int64_t, std::string>& chatId,
                                  std::int32_t messageId,
                                  bool disableNotification)
{

}

bool Telebot::Api::UnpinChatMessage(const boost::variant<std::int64_t, std::string>& chatId,
                                    std::int32_t messageId)
{

}

bool Telebot::Api::UnpinAllChatMessages(const boost::variant<std::int64_t, std::string>& chatId)
{

}

bool Telebot::Api::LeaveChat(const boost::variant<std::int64_t, std::string>& chatId)
{

}

Telebot::Chat::Ptr Telebot::Api::GetChat(const boost::variant<std::int64_t, std::string>& chatId)
{

}

std::vector<Telebot::ChatMember::Ptr>
Telebot::Api::GetChatAdministrators(const boost::variant<std::int64_t, std::string>& chatId)
{

}

std::int32_t Telebot::Api::GetChatMemberCount(const boost::variant<std::int64_t, std::string>& chatId)
{

}

Telebot::ChatMember::Ptr Telebot::Api::GetChatMember(const boost::variant<std::int64_t, std::string>& chatId,
                                                     std::int64_t userId)
{

}

bool Telebot::Api::SetChatStickerSet(const boost::variant<std::int64_t, std::string>& chatId,
                                     const std::string& stickerSetName)
{

}

bool Telebot::Api::DeleteChatStickerSet(const boost::variant<std::int64_t, std::string>& chatId)
{

}

std::vector<Telebot::Sticker::Ptr> Telebot::Api::GetForumTopicIconStickers()
{

}

Telebot::ForumTopic::Ptr Telebot::Api::CreateForumTopic(const boost::variant<std::int64_t, std::string>& chatId,
                                               const std::string& name,
                                               std::int32_t iconColor,
                                               const std::string& iconCustomEmojiId)
{

}

bool Telebot::Api::EditForumTopic(const boost::variant<std::int64_t, std::string>& chatId,
                                  std::int32_t messageThreadId,
                                  const std::string& name,
                                  const boost::variant<std::int8_t, std::string>& iconCustomEmojiId)
{

}

bool Telebot::Api::CloseForumTopic(const boost::variant<std::int64_t, std::string>& chatId,
                                   std::int32_t messageThreadId)
{

}

bool Telebot::Api::ReopenForumTopic(const boost::variant<std::int64_t, std::string>& chatId,
                                    std::int32_t messageThreadId)
{

}

bool Telebot::Api::DeleteForumTopic(const boost::variant<std::int64_t, std::string>& chatId,
                                    std::int32_t messageThreadId)
{

}

bool Telebot::Api::UnpinAllForumTopicMessages(const boost::variant<std::int64_t, std::string>& chatId,
                                              std::int32_t messageThreadId)
{

}

bool Telebot::Api::EditGeneralForumTopic(const boost::variant<std::int64_t, std::string>& chatId,
                                         const std::string& name)
{

}

bool Telebot::Api::CloseGeneralForumTopic(const boost::variant<std::int64_t, std::string>& chatId)
{

}

bool Telebot::Api::ReopenGeneralForumTopic(const boost::variant<std::int64_t, std::string>& chatId)
{

}

bool Telebot::Api::HideGeneralForumTopic(const boost::variant<std::int64_t, std::string>& chatId)
{

}

bool Telebot::Api::UnhideGeneralForumTopic(const boost::variant<std::int64_t, std::string>& chatId)
{

}

bool Telebot::Api::AnswerCallbackQuery(const std::string& callbackQueryId,
                                       const std::string& text,
                                       bool showAlert,
                                       const std::string& url,
                                       std::int32_t cacheTime)
{

}

bool Telebot::Api::SetMyCommands(const std::vector<BotCommand::Ptr>& commands,
                                 const BotCommandScope::Ptr& scope,
                                 const std::string& languageCode)
{

}

bool Telebot::Api::DeleteMyCommands(const BotCommandScope::Ptr& scope,
                                    const std::string& languageCode)
{

}

std::vector<Telebot::BotCommand::Ptr> Telebot::Api::GetMyCommands(const BotCommandScope::Ptr& scope,
                                                                  const std::string& languageCode)
{

}

bool SetMyDescription(const std::string& description,
                      const std::string& languageCode)
{

}

std::string Telebot::Api::GetMyDescription(const std::string& languageCode)
{

}

bool Telebot::Api::SetMyShortDescription(const std::string& shortDescription,
                                         const std::string& languageCode)
{

}

std::string Telebot::Api::GetMyShortDescription(const std::string& languageCode)
{

}

bool Telebot::Api::SetChatMenuButton(std::int64_t chatId,
                                     const MenuButton::Ptr& menuButton)
{

}

Telebot::MenuButton::Ptr Telebot::Api::GetChatMenuButton(std::int64_t chatId)
{

}

bool Telebot::Api::SetMyDefaultAdministratorRights(const ChatAdministratorRights::Ptr& rights,
                                                   bool forChannels)
{

}

Telebot::ChatAdministratorRights::Ptr Telebot::Api::GetMyDefaultAdministratorRights(bool forChannels)
{

}

Telebot::Message::Ptr Telebot::Api::EditMessageText(const std::string& text,
                                                    const boost::variant<std::int64_t, std::string>& chatId,
                                                    std::int32_t messageId,
                                                    const std::string& inlineMessageId,
                                                    const std::string& parseMode,
                                                    bool disableWebPagePreview,
                                                    const Telebot::GenericReply::Ptr& replyMarkup,
                                                    const std::vector<MessageEntity::Ptr>& entities)
{

}

Telebot::Message::Ptr Telebot::Api::EditMessageCaption(const boost::variant<std::int64_t, std::string>& chatId,
                                                       std::int32_t messageId,
                                                       const std::string& caption,
                                                       const std::string& inlineMessageId,
                                                       const Telebot::GenericReply::Ptr& replyMarkup,
                                                       const std::string& parseMode,
                                                       const std::vector<MessageEntity::Ptr>& captionEntities)
{

}

Telebot::Message::Ptr Telebot::Api::EditMessageMedia(const InputMedia::Ptr& media,
                                                     const boost::variant<std::int64_t, std::string>& chatId,
                                                     std::int32_t messageId,
                                                     const std::string& inlineMessageId,
                                                     const Telebot::GenericReply::Ptr& replyMarkup)
{

}

Telebot::Message::Ptr Telebot::Api::EditMessageLiveLocation(float latitude,
                                                            float longitude,
                                                            const boost::variant<std::int64_t, std::string>& chatId,
                                                            std::int32_t messageId,
                                                            const std::string& inlineMessageId,
                                                            const Telebot::InlineKeyboardMarkup::Ptr& replyMarkup,
                                                            float horizontalAccuracy,
                                                            std::int32_t heading,
                                                            std::int32_t proximityAlertRadius)
{

}

Telebot::Message::Ptr Telebot::Api::StopMessageLiveLocation(const boost::variant<std::int64_t, std::string>& chatId,
                                                            std::int32_t messageId,
                                                            const std::string& inlineMessageId,
                                                            const Telebot::InlineKeyboardMarkup::Ptr& replyMarkup)
{

}

Telebot::Message::Ptr Telebot::Api::EditMessageReplyMarkup(const boost::variant<std::int64_t, std::string>& chatId,
                                                           std::int32_t messageId,
                                                           const std::string& inlineMessageId,
                                                           const Telebot::GenericReply::Ptr& replyMarkup)
{

}

Telebot::Poll::Ptr Telebot::Api::StopPoll(const boost::variant<std::int64_t, std::string>& chatId,
                                          std::int64_t messageId,
                                          const Telebot::InlineKeyboardMarkup::Ptr& replyMarkup)
{

}

bool Telebot::Api::DeleteMessage(const boost::variant<std::int64_t, std::string>& chatId,
                                 std::int32_t messageId)
{

}

Telebot::Message::Ptr Telebot::Api::SendSticker(const boost::variant<std::int64_t, std::string>& chatId,
                                                const boost::variant<InputFile::Ptr, std::string>& sticker,
                                                std::int32_t replyToMessageId,
                                                const Telebot::GenericReply::Ptr& replyMarkup,
                                                bool disableNotification,
                                                bool allowSendingWithoutReply,
                                                bool protectContent,
                                                std::int32_t messageThreadId)
{

}

Telebot::StickerSet::Ptr Telebot::Api::GetStickerSet(const std::string& name)
{

}

std::vector<Telebot::Sticker::Ptr> Telebot::Api::GetCustomEmojiStickers(const std::vector<std::string>& customEmojiIds)
{

}

Telebot::File::Ptr Telebot::Api::UploadStickerFile(std::int64_t userId, const InputFile::Ptr& pngSticker)
{

}

bool Telebot::Api::CreateNewStickerSet(std::int64_t userId,
                                       const std::string& name,
                                       const std::string& title,
                                       const std::string& emojis,
                                       const MaskPosition::Ptr& maskPosition,
                                       const boost::variant<InputFile::Ptr, std::string>& pngSticker,
                                       const InputFile::Ptr& tgsSticker,
                                       const InputFile::Ptr& webmSticker,
                                       const std::string& stickerType)
{

}

bool Telebot::Api::AddStickerToSet(std::int64_t userId,
                                   const std::string& name,
                                   const std::string& emojis,
                                   const MaskPosition::Ptr& maskPosition,
                                   const boost::variant<InputFile::Ptr, std::string>& pngSticker,
                                   const InputFile::Ptr& tgsSticker,
                                   const InputFile::Ptr& webmSticker)
{

}

bool Telebot::Api::SetStickerPositionInSet(const std::string& sticker,
                                           std::int32_t position)
{

}

bool Telebot::Api::DeleteStickerFromSet(const std::string& sticker)
{

}

bool Telebot::Api::SetStickerEmojiList(const std::string& sticker,
                                       const std::vector<std::string>& emojiList)
{

}

bool Telebot::Api::SetStickerKeywords(const std::string& sticker,
                                      const std::vector<std::string>& keywords)
{

}

bool Telebot::Api::SetStickerMaskPosition(const std::string& sticker,
                                          const MaskPosition::Ptr& maskPosition)
{

}

bool Telebot::Api::SetStickerTitle(const std::string& name,
                                   const std::string& title)
{

}

bool Telebot::Api::SetStickerSetThumbnail(const std::string& name,
                                          std::int64_t userId,
                                          const boost::variant<InputFile::Ptr, std::string>& thumb)
{

}

bool Telebot::Api::SetCustomEmojiStickerSetThumbnail(const std::string& name,
                                                     const std::string& customEmojiId)
{

}

bool Telebot::Api::DeleteStickerSet(const std::string& name)
{

}

bool Telebot::Api::AnswerInlineQuery(const std::string& inlineQueryId,
                                     const std::vector<InlineQueryResult::Ptr>& results,
                                     std::int32_t cacheTime,
                                     bool isPersonal,
                                     const std::string& nextOffset,
                                     const std::string& switchPmText,
                                     const std::string& switchPmParameter)
{

}

Telebot::SentWebAppMessage::Ptr Telebot::Api::AnswerWebAppQuery(const std::string& webAppQueryId,
                                                                const InlineQueryResult::Ptr& result)
{

}

Telebot::Message::Ptr Telebot::Api::SendInvoice(const boost::variant<std::int64_t, std::string>& chatId,
                                                const std::string& title,
                                                const std::string& description,
                                                const std::string& payload,
                                                const std::string& providerToken,
                                                const std::string& currency,
                                                const std::vector<LabeledPrice::Ptr>& prices,
                                                const std::string& providerData,
                                                const std::string& photoUrl,
                                                std::int32_t photoSize,
                                                std::int32_t photoWidth,
                                                std::int32_t photoHeight,
                                                bool needName,
                                                bool needPhoneNumber,
                                                bool needEmail,
                                                bool needShippingAddress,
                                                bool sendPhoneNumberToProvider,
                                                bool sendEmailToProvider,
                                                bool isFlexible,
                                                std::int32_t replyToMessageId,
                                                const GenericReply::Ptr& replyMarkup,
                                                bool disableNotification,
                                                bool allowSendingWithoutReply,
                                                std::int32_t maxTipAmount,
                                                const std::vector<std::int32_t>& suggestedTipAmounts,
                                                const std::string& startParameter,
                                                bool protectContent,
                                                std::int32_t messageThreadId)
{

}

std::string Telebot::Api::CreateInvoiceLink(const std::string& title,
                                            const std::string& description,
                                            const std::string& payload,
                                            const std::string& providerToken,
                                            const std::string& currency,
                                            const std::vector<Telebot::LabeledPrice::Ptr>& prices,
                                            std::int32_t maxTipAmount,
                                            const std::vector<std::int32_t>& suggestedTipAmounts,
                                            const std::string& providerData,
                                            const std::string& photoUrl,
                                            std::int32_t photoSize,
                                            std::int32_t photoWidth,
                                            std::int32_t photoHeight,
                                            bool needName,
                                            bool needPhoneNumber,
                                            bool needEmail,
                                            bool needShippingAddress,
                                            bool sendPhoneNumberToProvider,
                                            bool sendEmailToProvider,
                                            bool isFlexible)
{

}

bool Telebot::Api::AnswerShippingQuery(const std::string& shippingQueryId,
                                       bool ok,
                                       const std::vector<ShippingOption::Ptr>& shippingOptions,
                                       const std::string& errorMessage)
{

}

bool Telebot::Api::AnswerPreCheckoutQuery(const std::string& preCheckoutQueryId,
                                          bool ok,
                                          const std::string& errorMessage)
{

}

bool Telebot::Api::SetPassportDataErrors(std::int64_t userId,
                                         const std::vector<PassportElementError::Ptr>& errors)
{

}

Telebot::Message::Ptr Telebot::Api::SendGame(std::int64_t chatId,
                                             const std::string& gameShortName,
                                             std::int32_t replyToMessageId,
                                             const InlineKeyboardMarkup::Ptr& replyMarkup,
                                             bool disableNotification,
                                             bool allowSendingWithoutReply,
                                             bool protectContent,
                                             std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SetGameScore(std::int64_t userId,
                                                 std::int32_t score,
                                                 bool force,
                                                 bool disableEditMessage,
                                                 std::int64_t chatId,
                                                 std::int32_t messageId,
                                                 const std::string& inlineMessageId)
{

}

std::vector<Telebot::GameHighScore::Ptr> Telebot::Api::GetGameHighScores(std::int64_t userId,
                                                                         std::int64_t chatId,
                                                                         std::int32_t messageId,
                                                                         const std::string& inlineMessageId)
{

}