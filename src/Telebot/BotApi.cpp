#include "Telebot/BotApi.h"

const std::string Telebot::BotApi::HOST = "api.telegram.org";
const unsigned int Telebot::BotApi::HTTP_VERSION = 11;

Telebot::BotApi::BotApi(const std::string& token)
{
    _token = token;
}

Json Telebot::BotApi::Get(const std::string& methodName)
{
    Common::HttpContext::Ptr httpContext = std::make_shared<Common::HttpContext>();
    httpContext->Request->version(HTTP_VERSION);
    httpContext->Request->method_string("GET");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/bot" + _token + "/" + methodName);

    Common::HttpsClient::SendHttpsAsync(httpContext);
    Json json = Json::parse(httpContext->Response->get().body());
    if (json.at("ok").get<bool>()) return json.at("result");
}

Json Telebot::BotApi::Post(const std::string& methodName, const Json& params)
{
    Common::HttpContext::Ptr httpContext = std::make_shared<Common::HttpContext>();
    httpContext->Request->version(HTTP_VERSION);
    httpContext->Request->method_string("POST");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/bot" + _token + "/" + methodName);

    httpContext->Request->set(boost::beast::http::field::content_type, "application/json");
    httpContext->Request->body() = params.dump();
    httpContext->Request->prepare_payload();

    Common::HttpsClient::SendHttpsAsync(httpContext);
    Json json = Json::parse(httpContext->Response->get().body());
    if (json.at("ok").get<bool>()) return json.at("result");
}

std::vector<Telebot::Update::Ptr> Telebot::BotApi::GetUpdates(int offset,
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

bool Telebot::BotApi::SetWebhook(const std::string &url,
                                 const InputFile::Ptr& certificate,
                                 std::int32_t maxConnections,
                                 const std::vector<std::string> &allowedUpdates,
                                 const std::string &ipAddress,
                                 bool dropPendingUpdates,
                                 const std::string &secretToken)
{

}

bool Telebot::BotApi::DeleteWebhook(bool dropPendingUpdates)
{

}

Telebot::WebhookInfo::Ptr Telebot::BotApi::GetWebhookInfo()
{

}

Telebot::User::Ptr Telebot::BotApi::GetMe()
{
    Json responseBody = Get("getMe");

    User::Ptr user = std::make_shared<User>();
    *user = responseBody.get<User>();
    return user;
}

bool Telebot::BotApi::LogOut()
{

}

bool Telebot::BotApi::Close()
{

}

Telebot::Message::Ptr Telebot::BotApi::SendMessage(std::int64_t chatId,
                                                   const std::string& text,
                                                   bool disableWebPagePreview,
                                                   std::int32_t replyToMessageId,
                                                   const GenericReply::Ptr& replyMarkup,
                                                   const std::string& parseMode,
                                                   bool disableNotification,
                                                   const std::vector<MessageEntity::Ptr>& entities,
                                                   bool allowSendingWithoutReply,
                                                   bool protectContent,
                                                   std::int32_t messageThreadId)
{
    Json requestBody;
    requestBody["chat_id"] = chatId;
    requestBody["text"] = text;
    Json responseBody = Post("sendMessage", requestBody);

    Message::Ptr message = std::make_shared<Message>();
    *message = responseBody.get<Message>();
    return message;
}

Telebot::Message::Ptr Telebot::BotApi::ForwardMessage(std::int64_t chatId,
                                                      std::int64_t fromChatId,
                                                      std::int32_t messageId,
                                                      bool disableNotification,
                                                      bool protectContent,
                                                      std::int32_t messageThreadId)
{

}

Telebot::MessageId::Ptr Telebot::BotApi::CopyMessage(std::int64_t chatId,
                                                     std::int64_t fromChatId,
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

Telebot::Message::Ptr Telebot::BotApi::SendPhoto(std::int64_t chatId,
                                                 const InputFile::Ptr& photo,
                                                 const std::string& caption,
                                                 std::int32_t replyToMessageId,
                                                 const GenericReply::Ptr& replyMarkup,
                                                 const std::string& parseMode,
                                                 bool disableNotification,
                                                 const std::vector<MessageEntity::Ptr>& captionEntities,
                                                 bool allowSendingWithoutReply,
                                                 bool protectContent,
                                                 std::int32_t messageThreadId,
                                                 bool hasSpoiler)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendAudio(std::int64_t chatId,
                                                 const InputFile::Ptr& audio,
                                                 const std::string& caption,
                                                 std::int32_t duration,
                                                 const std::string& performer,
                                                 const std::string& title,
                                                 const InputFile::Ptr& thumb,
                                                 std::int32_t replyToMessageId,
                                                 const GenericReply::Ptr& replyMarkup,
                                                 const std::string& parseMode,
                                                 bool disableNotification,
                                                 const std::vector<MessageEntity::Ptr>& captionEntities,
                                                 bool allowSendingWithoutReply,
                                                 bool protectContent,
                                                 std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendDocument(std::int64_t chatId,
                                                    const InputFile::Ptr& document,
                                                    const InputFile::Ptr& thumb,
                                                    const std::string& caption,
                                                    std::int32_t replyToMessageId,
                                                    const GenericReply::Ptr& replyMarkup,
                                                    const std::string& parseMode,
                                                    bool disableNotification,
                                                    const std::vector<MessageEntity::Ptr>& captionEntities,
                                                    bool disableContentTypeDetection,
                                                    bool allowSendingWithoutReply,
                                                    bool protectContent,
                                                    std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendVideo(std::int64_t chatId,
                                                 const InputFile::Ptr& video,
                                                 bool supportsStreaming,
                                                 std::int32_t duration,
                                                 std::int32_t width,
                                                 std::int32_t height,
                                                 const InputFile::Ptr& thumb,
                                                 const std::string &caption,
                                                 std::int32_t replyToMessageId,
                                                 const GenericReply::Ptr& replyMarkup,
                                                 const std::string &parseMode,
                                                 bool disableNotification,
                                                 const std::vector<MessageEntity::Ptr>& captionEntities,
                                                 bool allowSendingWithoutReply,
                                                 bool protectContent,
                                                 std::int32_t messageThreadId,
                                                 bool hasSpoiler)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendAnimation(std::int64_t chatId,
                                                     const InputFile::Ptr& animation,
                                                     std::int32_t duration,
                                                     std::int32_t width,
                                                     std::int32_t height,
                                                     const InputFile::Ptr& thumb,
                                                     const std::string& caption,
                                                     std::int32_t replyToMessageId,
                                                     const GenericReply::Ptr& replyMarkup,
                                                     const std::string &parseMode,
                                                     bool disableNotification,
                                                     const std::vector<MessageEntity::Ptr>& captionEntities,
                                                     bool allowSendingWithoutReply,
                                                     bool protectContent,
                                                     std::int32_t messageThreadId,
                                                     bool hasSpoiler)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendVoice(std::int64_t chatId,
                                                 const InputFile::Ptr& voice,
                                                 const std::string& caption,
                                                 std::int32_t duration,
                                                 std::int32_t replyToMessageId,
                                                 const GenericReply::Ptr& replyMarkup,
                                                 const std::string& parseMode,
                                                 bool disableNotification,
                                                 const std::vector<MessageEntity::Ptr>& captionEntities,
                                                 bool allowSendingWithoutReply,
                                                 bool protectContent,
                                                 std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendVideoNote(std::int64_t chatId,
                                                     const InputFile::Ptr& videoNote,
                                                     std::int64_t replyToMessageId,
                                                     bool disableNotification,
                                                     std::int32_t duration,
                                                     std::int32_t length,
                                                     const InputFile::Ptr& thumb,
                                                     const GenericReply::Ptr& replyMarkup,
                                                     bool allowSendingWithoutReply,
                                                     bool protectContent,
                                                     std::int32_t messageThreadId)
{

}

std::vector<Telebot::Message::Ptr> Telebot::BotApi::SendMediaGroup(std::int64_t chatId,
                                                                   const std::vector<InputMedia::Ptr>& media,
                                                                   bool disableNotification,
                                                                   std::int32_t replyToMessageId,
                                                                   bool allowSendingWithoutReply,
                                                                   bool protectContent,
                                                                   std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendLocation(std::int64_t chatId,
                                                    float latitude,
                                                    float longitude,
                                                    std::int32_t livePeriod,
                                                    std::int32_t replyToMessageId,
                                                    const GenericReply::Ptr& replyMarkup,
                                                    bool disableNotification,
                                                    float horizontalAccuracy,
                                                    std::int32_t heading,
                                                    std::int32_t proximityAlertRadius,
                                                    bool allowSendingWithoutReply,
                                                    bool protectContent,
                                                    std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendVenue(std::int64_t chatId,
                                                 float latitude,
                                                 float longitude,
                                                 const std::string& title,
                                                 const std::string& address,
                                                 const std::string& foursquareId,
                                                 const std::string& foursquareType,
                                                 bool disableNotification,
                                                 std::int32_t replyToMessageId,
                                                 const GenericReply::Ptr& replyMarkup,
                                                 const std::string& googlePlaceId,
                                                 const std::string& googlePlaceType,
                                                 bool allowSendingWithoutReply,
                                                 bool protectContent,
                                                 std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendContact(std::int64_t chatId,
                                                   const std::string& phoneNumber,
                                                   const std::string& firstName,
                                                   const std::string& lastName,
                                                   const std::string& vcard,
                                                   bool disableNotification,
                                                   std::int32_t replyToMessageId,
                                                   const GenericReply::Ptr& replyMarkup,
                                                   bool allowSendingWithoutReply,
                                                   bool protectContent,
                                                   std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendPoll(std::int64_t chatId,
                                                const std::string& question,
                                                const std::vector<std::string>& options,
                                                bool disableNotification,
                                                std::int32_t replyToMessageId,
                                                const GenericReply::Ptr& replyMarkup,
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

Telebot::Message::Ptr Telebot::BotApi::SendDice(const std::int64_t chatId,
                                                bool disableNotification,
                                                std::int32_t replyToMessageId,
                                                const GenericReply::Ptr& replyMarkup,
                                                const std::string& emoji,
                                                bool allowSendingWithoutReply,
                                                bool protectContent,
                                                std::int32_t messageThreadId)
{

}

bool Telebot::BotApi::SendChatAction(std::int64_t chatId,
                                     const std::string& action,
                                     std::int32_t messageThreadId)
{

}

Telebot::UserProfilePhotos::Ptr Telebot::BotApi::GetUserProfilePhotos(std::int64_t userId,
                                                                      std::int32_t offset,
                                                                      std::int32_t limit)
{

}

Telebot::File::Ptr Telebot::BotApi::GetFile(const std::string& fileId)
{

}

bool Telebot::BotApi::BanChatMember(std::int64_t chatId,
                                    std::int64_t userId,
                                    std::int32_t untilDate,
                                    bool revokeMessages)
{

}

bool Telebot::BotApi::UnbanChatMember(std::int64_t chatId,
                                      std::int64_t userId,
                                      bool onlyIfBanned)
{

}

bool Telebot::BotApi::RestrictChatMember(std::int64_t chatId,
                                         std::int64_t userId,
                                         const ChatPermissions::Ptr& permissions,
                                         std::int64_t untilDate,
                                         bool useIndependentChatPermissions)
{

}

bool Telebot::BotApi::PromoteChatMember(std::int64_t chatId,
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

bool Telebot::BotApi::SetChatAdministratorCustomTitle(std::int64_t chatId,
                                                      std::int64_t userId,
                                                      const std::string& customTitle)
{

}

bool Telebot::BotApi::BanChatSenderChat(std::int64_t chatId,
                                        std::int64_t senderChatId)
{

}

bool Telebot::BotApi::UnbanChatSenderChat(std::int64_t chatId,
                                          std::int64_t senderChatId)
{

}

bool Telebot::BotApi::SetChatPermissions(std::int64_t chatId,
                                         const ChatPermissions::Ptr& permissions,
                                         bool useIndependentChatPermissions)
{

}

std::string Telebot::BotApi::ExportChatInviteLink(std::int64_t chatId)
{

}

Telebot::ChatInviteLink::Ptr Telebot::BotApi::CreateChatInviteLink(std::int64_t chatId,
                                                                   std::int32_t expireDate,
                                                                   std::int32_t memberLimit,
                                                                   const std::string& name,
                                                                   bool createsJoinRequest)
{

}

Telebot::ChatInviteLink::Ptr Telebot::BotApi::EditChatInviteLink(std::int64_t chatId,
                                                                 const std::string& inviteLink,
                                                                 std::int32_t expireDate,
                                                                 std::int32_t memberLimit,
                                                                 const std::string& name,
                                                                 bool createsJoinRequest)
{

}

Telebot::ChatInviteLink::Ptr Telebot::BotApi::RevokeChatInviteLink(std::int64_t chatId,
                                                                   const std::string& inviteLink)
{

}

bool Telebot::BotApi::ApproveChatJoinRequest(std::int64_t chatId,
                                             std::int64_t userId)
{

}

bool Telebot::BotApi::DeclineChatJoinRequest(std::int64_t chatId,
                                             std::int64_t userId)
{

}

bool Telebot::BotApi::SetChatPhoto(std::int64_t chatId,
                                   const InputFile::Ptr& photo)
{

}

bool Telebot::BotApi::DeleteChatPhoto(std::int64_t chatId)
{

}

bool Telebot::BotApi::SetChatTitle(std::int64_t chatId,
                                   const std::string& title)
{

}

bool Telebot::BotApi::SetChatDescription(std::int64_t chatId,
                                         const std::string& description)
{

}

bool Telebot::BotApi::PinChatMessage(std::int64_t chatId,
                                     std::int32_t messageId,
                                     bool disableNotification)
{

}

bool Telebot::BotApi::UnpinChatMessage(std::int64_t chatId,
                                       std::int32_t messageId)
{

}

bool Telebot::BotApi::UnpinAllChatMessages(std::int64_t chatId)
{

}

bool Telebot::BotApi::LeaveChat(std::int64_t chatId)
{

}

Telebot::Chat::Ptr Telebot::BotApi::GetChat(std::int64_t chatId)
{

}

std::vector<Telebot::ChatMember::Ptr> Telebot::BotApi::GetChatAdministrators(std::int64_t chatId)
{

}

std::int32_t Telebot::BotApi::GetChatMemberCount(std::int64_t chatId)
{

}

Telebot::ChatMember::Ptr Telebot::BotApi::GetChatMember(std::int64_t chatId,
                                                        std::int64_t userId)
{

}

bool Telebot::BotApi::SetChatStickerSet(std::int64_t chatId,
                                        const std::string& stickerSetName)
{

}

bool Telebot::BotApi::DeleteChatStickerSet(std::int64_t chatId)
{

}

std::vector<Telebot::Sticker::Ptr> Telebot::BotApi::GetForumTopicIconStickers()
{

}

Telebot::ForumTopic::Ptr Telebot::BotApi::CreateForumTopic(std::int64_t chatId,
                                                           const std::string& name,
                                                           std::int32_t iconColor,
                                                           const std::string& iconCustomEmojiId)
{

}

bool Telebot::BotApi::EditForumTopic(std::int64_t chatId,
                                     std::int32_t messageThreadId,
                                     const std::string& name,
                                     std::int8_t iconCustomEmojiId)
{

}

bool Telebot::BotApi::CloseForumTopic(std::int64_t chatId,
                                      std::int32_t messageThreadId)
{

}

bool Telebot::BotApi::ReopenForumTopic(std::int64_t chatId,
                                       std::int32_t messageThreadId)
{

}

bool Telebot::BotApi::DeleteForumTopic(std::int64_t chatId,
                                       std::int32_t messageThreadId)
{

}

bool Telebot::BotApi::UnpinAllForumTopicMessages(std::int64_t chatId,
                                                 std::int32_t messageThreadId)
{

}

bool Telebot::BotApi::EditGeneralForumTopic(std::int64_t chatId,
                                            const std::string& name)
{

}

bool Telebot::BotApi::CloseGeneralForumTopic(std::int64_t chatId)
{

}

bool Telebot::BotApi::ReopenGeneralForumTopic(std::int64_t chatId)
{

}

bool Telebot::BotApi::HideGeneralForumTopic(std::int64_t chatId)
{

}

bool Telebot::BotApi::UnhideGeneralForumTopic(std::int64_t chatId)
{

}

bool Telebot::BotApi::AnswerCallbackQuery(const std::string& callbackQueryId,
                                          const std::string& text,
                                          bool showAlert,
                                          const std::string& url,
                                          std::int32_t cacheTime)
{

}

bool Telebot::BotApi::SetMyCommands(const std::vector<BotCommand::Ptr>& commands,
                                    const BotCommandScope::Ptr& scope,
                                    const std::string& languageCode)
{
    Json requestBody;
    Json commandsArray;
    for (const BotCommand::Ptr& command : commands)
        commandsArray.push_back(*command);
    requestBody["commands"] = commandsArray;
    if (scope.get() != nullptr) requestBody["scope"] = *scope;
    if (!languageCode.empty()) requestBody["language_code"] = languageCode;
    Json responseBody = Post("setMyCommands", requestBody);

    return responseBody.get<bool>();
}

bool Telebot::BotApi::DeleteMyCommands(const BotCommandScope::Ptr& scope,
                                       const std::string& languageCode)
{

}

std::vector<Telebot::BotCommand::Ptr> Telebot::BotApi::GetMyCommands(const BotCommandScope::Ptr& scope,
                                                                     const std::string& languageCode)
{

}

bool SetMyDescription(const std::string& description,
                      const std::string& languageCode)
{

}

std::string Telebot::BotApi::GetMyDescription(const std::string& languageCode)
{

}

bool Telebot::BotApi::SetMyShortDescription(const std::string& shortDescription,
                                            const std::string& languageCode)
{

}

std::string Telebot::BotApi::GetMyShortDescription(const std::string& languageCode)
{

}

bool Telebot::BotApi::SetChatMenuButton(std::int64_t chatId,
                                        const MenuButton::Ptr& menuButton)
{

}

Telebot::MenuButton::Ptr Telebot::BotApi::GetChatMenuButton(std::int64_t chatId)
{

}

bool Telebot::BotApi::SetMyDefaultAdministratorRights(const ChatAdministratorRights::Ptr& rights,
                                                      bool forChannels)
{

}

Telebot::ChatAdministratorRights::Ptr Telebot::BotApi::GetMyDefaultAdministratorRights(bool forChannels)
{

}

Telebot::Message::Ptr Telebot::BotApi::EditMessageText(const std::string& text,
                                                       std::int64_t chatId,
                                                       std::int32_t messageId,
                                                       const std::string& inlineMessageId,
                                                       const std::string& parseMode,
                                                       bool disableWebPagePreview,
                                                       const GenericReply::Ptr& replyMarkup,
                                                       const std::vector<MessageEntity::Ptr>& entities)
{

}

Telebot::Message::Ptr Telebot::BotApi::EditMessageCaption(std::int64_t chatId,
                                                          std::int32_t messageId,
                                                          const std::string& caption,
                                                          const std::string& inlineMessageId,
                                                          const GenericReply::Ptr& replyMarkup,
                                                          const std::string& parseMode,
                                                          const std::vector<MessageEntity::Ptr>& captionEntities)
{

}

Telebot::Message::Ptr Telebot::BotApi::EditMessageMedia(const InputMedia::Ptr& media,
                                                        const std::int64_t chatId,
                                                        std::int32_t messageId,
                                                        const std::string& inlineMessageId,
                                                        const Telebot::GenericReply::Ptr& replyMarkup)
{

}

Telebot::Message::Ptr Telebot::BotApi::EditMessageLiveLocation(float latitude,
                                                               float longitude,
                                                               const std::int64_t chatId,
                                                               std::int32_t messageId,
                                                               const std::string& inlineMessageId,
                                                               const InlineKeyboardMarkup::Ptr& replyMarkup,
                                                               float horizontalAccuracy,
                                                               std::int32_t heading,
                                                               std::int32_t proximityAlertRadius)
{

}

Telebot::Message::Ptr Telebot::BotApi::StopMessageLiveLocation(const std::int64_t chatId,
                                                               std::int32_t messageId,
                                                               const std::string& inlineMessageId,
                                                               const InlineKeyboardMarkup::Ptr& replyMarkup)
{

}

Telebot::Message::Ptr Telebot::BotApi::EditMessageReplyMarkup(const std::int64_t chatId,
                                                              std::int32_t messageId,
                                                              const std::string& inlineMessageId,
                                                              const GenericReply::Ptr& replyMarkup)
{

}

Telebot::Poll::Ptr Telebot::BotApi::StopPoll(std::int64_t chatId,
                                             std::int64_t messageId,
                                             const InlineKeyboardMarkup::Ptr& replyMarkup)
{

}

bool Telebot::BotApi::DeleteMessage(std::int64_t chatId,
                                    std::int32_t messageId)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendSticker(std::int64_t chatId,
                                                   const InputFile::Ptr& sticker,
                                                   std::int32_t replyToMessageId,
                                                   const GenericReply::Ptr& replyMarkup,
                                                   bool disableNotification,
                                                   bool allowSendingWithoutReply,
                                                   bool protectContent,
                                                   std::int32_t messageThreadId)
{

}

Telebot::StickerSet::Ptr Telebot::BotApi::GetStickerSet(const std::string& name)
{

}

std::vector<Telebot::Sticker::Ptr> Telebot::BotApi::GetCustomEmojiStickers(const std::vector<std::string>& customEmojiIds)
{

}

Telebot::File::Ptr Telebot::BotApi::UploadStickerFile(std::int64_t userId,
                                                      const InputFile::Ptr& pngSticker)
{

}

bool Telebot::BotApi::CreateNewStickerSet(std::int64_t userId,
                                          const std::string& name,
                                          const std::string& title,
                                          const std::string& emojis,
                                          const MaskPosition::Ptr& maskPosition,
                                          const InputFile::Ptr& pngSticker,
                                          const InputFile::Ptr& tgsSticker,
                                          const InputFile::Ptr& webmSticker,
                                          const std::string& stickerType)
{

}

bool Telebot::BotApi::AddStickerToSet(std::int64_t userId,
                                      const std::string& name,
                                      const std::string& emojis,
                                      const MaskPosition::Ptr& maskPosition,
                                      const InputFile::Ptr& pngSticker,
                                      const InputFile::Ptr& tgsSticker,
                                      const InputFile::Ptr& webmSticker)
{

}

bool Telebot::BotApi::SetStickerPositionInSet(const std::string& sticker,
                                              std::int32_t position)
{

}

bool Telebot::BotApi::DeleteStickerFromSet(const std::string& sticker)
{

}

bool Telebot::BotApi::SetStickerEmojiList(const std::string& sticker,
                                          const std::vector<std::string>& emojiList)
{

}

bool Telebot::BotApi::SetStickerKeywords(const std::string& sticker,
                                         const std::vector<std::string>& keywords)
{

}

bool Telebot::BotApi::SetStickerMaskPosition(const std::string& sticker,
                                             const MaskPosition::Ptr& maskPosition)
{

}

bool Telebot::BotApi::SetStickerTitle(const std::string& name,
                                      const std::string& title)
{

}

bool Telebot::BotApi::SetStickerSetThumbnail(const std::string& name,
                                             std::int64_t userId,
                                             const InputFile::Ptr& thumb)
{

}

bool Telebot::BotApi::SetCustomEmojiStickerSetThumbnail(const std::string& name,
                                                        const std::string& customEmojiId)
{

}

bool Telebot::BotApi::DeleteStickerSet(const std::string& name)
{

}

bool Telebot::BotApi::AnswerInlineQuery(const std::string& inlineQueryId,
                                        const std::vector<InlineQueryResult::Ptr>& results,
                                        std::int32_t cacheTime,
                                        bool isPersonal,
                                        const std::string& nextOffset,
                                        const std::string& switchPmText,
                                        const std::string& switchPmParameter)
{

}

Telebot::SentWebAppMessage::Ptr Telebot::BotApi::AnswerWebAppQuery(const std::string& webAppQueryId,
                                                                   const InlineQueryResult::Ptr& result)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendInvoice(std::int64_t chatId,
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

std::string Telebot::BotApi::CreateInvoiceLink(const std::string& title,
                                               const std::string& description,
                                               const std::string& payload,
                                               const std::string& providerToken,
                                               const std::string& currency,
                                               const std::vector<LabeledPrice::Ptr>& prices,
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

bool Telebot::BotApi::AnswerShippingQuery(const std::string& shippingQueryId,
                                          bool ok,
                                          const std::vector<ShippingOption::Ptr>& shippingOptions,
                                          const std::string& errorMessage)
{

}

bool Telebot::BotApi::AnswerPreCheckoutQuery(const std::string& preCheckoutQueryId,
                                             bool ok,
                                             const std::string& errorMessage)
{

}

bool Telebot::BotApi::SetPassportDataErrors(std::int64_t userId,
                                            const std::vector<PassportElementError::Ptr>& errors)
{

}

Telebot::Message::Ptr Telebot::BotApi::SendGame(std::int64_t chatId,
                                                const std::string& gameShortName,
                                                std::int32_t replyToMessageId,
                                                const InlineKeyboardMarkup::Ptr& replyMarkup,
                                                bool disableNotification,
                                                bool allowSendingWithoutReply,
                                                bool protectContent,
                                                std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::BotApi::SetGameScore(std::int64_t userId,
                                                    std::int32_t score,
                                                    bool force,
                                                    bool disableEditMessage,
                                                    std::int64_t chatId,
                                                    std::int32_t messageId,
                                                    const std::string& inlineMessageId)
{

}

std::vector<Telebot::GameHighScore::Ptr> Telebot::BotApi::GetGameHighScores(std::int64_t userId,
                                                                            std::int64_t chatId,
                                                                            std::int32_t messageId,
                                                                            const std::string& inlineMessageId)
{

}