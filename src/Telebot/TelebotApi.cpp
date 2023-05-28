#include "Telebot/TelebotApi.h"

const std::string Telebot::TelebotApi::HOST = "api.telegram.org";
const unsigned int Telebot::TelebotApi::HTTP_VERSION = 11;

Telebot::TelebotApi::TelebotApi(const std::string& token)
{
    _token = token;
}

Json Telebot::TelebotApi::Get(const std::string& methodName)
{
    auto httpContext = std::make_shared<Common::HttpContext<Common::EmptyBody, Common::StringBody>>();
    httpContext->Request->version(HTTP_VERSION);
    httpContext->Request->method_string("GET");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/bot" + _token + "/" + methodName);

    Common::HttpsClient::SendHttpsAsync(httpContext);
    Json json = Json::parse(httpContext->Response->get().body());
    if (json.at("ok").get<bool>()) return json.at("result");
}

Json Telebot::TelebotApi::Post(const std::string& methodName, const Json& params)
{
    auto httpContext = std::make_shared<Common::HttpContext<Common::StringBody, Common::StringBody>>();
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

std::vector<Telebot::Update::Ptr> Telebot::TelebotApi::GetUpdates(int offset,
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

bool Telebot::TelebotApi::SetWebhook(const std::string &url,
                                     const InputFile::Ptr& certificate,
                                     std::int32_t maxConnections,
                                     const std::vector<std::string> &allowedUpdates,
                                     const std::string &ipAddress,
                                     bool dropPendingUpdates,
                                     const std::string &secretToken)
{

}

bool Telebot::TelebotApi::DeleteWebhook(bool dropPendingUpdates)
{

}

Telebot::WebhookInfo::Ptr Telebot::TelebotApi::GetWebhookInfo()
{

}

Telebot::User::Ptr Telebot::TelebotApi::GetMe()
{
    Json responseBody = Get("getMe");

    User::Ptr user = std::make_shared<User>();
    *user = responseBody.get<User>();
    return user;
}

bool Telebot::TelebotApi::LogOut()
{

}

bool Telebot::TelebotApi::Close()
{

}

Telebot::Message::Ptr Telebot::TelebotApi::SendMessage(std::int64_t chatId,
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
    if (replyMarkup.get() != nullptr) requestBody["reply_markup"] = replyMarkup;
    Json responseBody = Post("sendMessage", requestBody);

    Message::Ptr message = std::make_shared<Message>();
    *message = responseBody.get<Message>();
    return message;
}

Telebot::Message::Ptr Telebot::TelebotApi::ForwardMessage(std::int64_t chatId,
                                                          std::int64_t fromChatId,
                                                          std::int32_t messageId,
                                                          bool disableNotification,
                                                          bool protectContent,
                                                          std::int32_t messageThreadId)
{

}

Telebot::MessageId::Ptr Telebot::TelebotApi::CopyMessage(std::int64_t chatId,
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

Telebot::Message::Ptr Telebot::TelebotApi::SendPhoto(std::int64_t chatId,
                                                     const boost::variant<std::string, InputFile::Ptr>& photo,
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
    if (photo.type() == typeid(std::string))
    {
        Json requestBody;
        requestBody["chat_id"] = chatId;
        requestBody["photo"] = boost::get<std::string>(photo);
        Json responseBody = Post("sendPhoto", requestBody);

        Message::Ptr message = std::make_shared<Message>();
        *message = responseBody.get<Message>();
        return message;
    }
    else
    {
        throw std::invalid_argument("photo must be std::string type");
    }
}

Telebot::Message::Ptr Telebot::TelebotApi::SendAudio(std::int64_t chatId,
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

Telebot::Message::Ptr Telebot::TelebotApi::SendDocument(std::int64_t chatId,
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

Telebot::Message::Ptr Telebot::TelebotApi::SendVideo(std::int64_t chatId,
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

Telebot::Message::Ptr Telebot::TelebotApi::SendAnimation(std::int64_t chatId,
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

Telebot::Message::Ptr Telebot::TelebotApi::SendVoice(std::int64_t chatId,
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

Telebot::Message::Ptr Telebot::TelebotApi::SendVideoNote(std::int64_t chatId,
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

std::vector<Telebot::Message::Ptr> Telebot::TelebotApi::SendMediaGroup(std::int64_t chatId,
                                                                       const std::vector<InputMedia::Ptr>& media,
                                                                       bool disableNotification,
                                                                       std::int32_t replyToMessageId,
                                                                       bool allowSendingWithoutReply,
                                                                       bool protectContent,
                                                                       std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::TelebotApi::SendLocation(std::int64_t chatId,
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

Telebot::Message::Ptr Telebot::TelebotApi::SendVenue(std::int64_t chatId,
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

Telebot::Message::Ptr Telebot::TelebotApi::SendContact(std::int64_t chatId,
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

Telebot::Message::Ptr Telebot::TelebotApi::SendPoll(std::int64_t chatId,
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

Telebot::Message::Ptr Telebot::TelebotApi::SendDice(const std::int64_t chatId,
                                                    bool disableNotification,
                                                    std::int32_t replyToMessageId,
                                                    const GenericReply::Ptr& replyMarkup,
                                                    const std::string& emoji,
                                                    bool allowSendingWithoutReply,
                                                    bool protectContent,
                                                    std::int32_t messageThreadId)
{

}

bool Telebot::TelebotApi::SendChatAction(std::int64_t chatId,
                                         const std::string& action,
                                         std::int32_t messageThreadId)
{

}

Telebot::UserProfilePhotos::Ptr Telebot::TelebotApi::GetUserProfilePhotos(std::int64_t userId,
                                                                          std::int32_t offset,
                                                                          std::int32_t limit)
{

}

Telebot::File::Ptr Telebot::TelebotApi::GetFile(const std::string& fileId)
{
    Json requestBody;
    requestBody["file_id"] = fileId;
    Json responseBody = Post("getFile", requestBody);

    File::Ptr file = std::make_shared<File>();
    *file = responseBody.get<File>();
    return file;
}

std::string Telebot::TelebotApi::DownloadFile(const File::Ptr& file, const std::string& toDirectory)
{
    auto httpContext = std::make_shared<Common::HttpContext<Common::EmptyBody, Common::FileBody>>();
    httpContext->Request->version(HTTP_VERSION);
    httpContext->Request->method_string("GET");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/file/bot" + _token + "/" + file->file_path);

    boost::filesystem::path path(file->file_path);
    std::string filePath = toDirectory + "/" + file->file_unique_id + path.extension().string();
    boost::beast::error_code ec;
    httpContext->Response->get().body().open(filePath.c_str(), boost::beast::file_mode::write, ec);

    Common::HttpsClient::SendHttpsAsync(httpContext);
    return filePath;
}

bool Telebot::TelebotApi::BanChatMember(std::int64_t chatId,
                                        std::int64_t userId,
                                        std::int32_t untilDate,
                                        bool revokeMessages)
{

}

bool Telebot::TelebotApi::UnbanChatMember(std::int64_t chatId,
                                          std::int64_t userId,
                                          bool onlyIfBanned)
{

}

bool Telebot::TelebotApi::RestrictChatMember(std::int64_t chatId,
                                             std::int64_t userId,
                                             const ChatPermissions::Ptr& permissions,
                                             std::int64_t untilDate,
                                             bool useIndependentChatPermissions)
{

}

bool Telebot::TelebotApi::PromoteChatMember(std::int64_t chatId,
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

bool Telebot::TelebotApi::SetChatAdministratorCustomTitle(std::int64_t chatId,
                                                          std::int64_t userId,
                                                          const std::string& customTitle)
{

}

bool Telebot::TelebotApi::BanChatSenderChat(std::int64_t chatId,
                                            std::int64_t senderChatId)
{

}

bool Telebot::TelebotApi::UnbanChatSenderChat(std::int64_t chatId,
                                              std::int64_t senderChatId)
{

}

bool Telebot::TelebotApi::SetChatPermissions(std::int64_t chatId,
                                             const ChatPermissions::Ptr& permissions,
                                             bool useIndependentChatPermissions)
{

}

std::string Telebot::TelebotApi::ExportChatInviteLink(std::int64_t chatId)
{

}

Telebot::ChatInviteLink::Ptr Telebot::TelebotApi::CreateChatInviteLink(std::int64_t chatId,
                                                                       std::int32_t expireDate,
                                                                       std::int32_t memberLimit,
                                                                       const std::string& name,
                                                                       bool createsJoinRequest)
{

}

Telebot::ChatInviteLink::Ptr Telebot::TelebotApi::EditChatInviteLink(std::int64_t chatId,
                                                                     const std::string& inviteLink,
                                                                     std::int32_t expireDate,
                                                                     std::int32_t memberLimit,
                                                                     const std::string& name,
                                                                     bool createsJoinRequest)
{

}

Telebot::ChatInviteLink::Ptr Telebot::TelebotApi::RevokeChatInviteLink(std::int64_t chatId,
                                                                       const std::string& inviteLink)
{

}

bool Telebot::TelebotApi::ApproveChatJoinRequest(std::int64_t chatId,
                                                 std::int64_t userId)
{

}

bool Telebot::TelebotApi::DeclineChatJoinRequest(std::int64_t chatId,
                                                 std::int64_t userId)
{

}

bool Telebot::TelebotApi::SetChatPhoto(std::int64_t chatId,
                                       const InputFile::Ptr& photo)
{

}

bool Telebot::TelebotApi::DeleteChatPhoto(std::int64_t chatId)
{

}

bool Telebot::TelebotApi::SetChatTitle(std::int64_t chatId,
                                       const std::string& title)
{

}

bool Telebot::TelebotApi::SetChatDescription(std::int64_t chatId,
                                             const std::string& description)
{

}

bool Telebot::TelebotApi::PinChatMessage(std::int64_t chatId,
                                         std::int32_t messageId,
                                         bool disableNotification)
{

}

bool Telebot::TelebotApi::UnpinChatMessage(std::int64_t chatId,
                                           std::int32_t messageId)
{

}

bool Telebot::TelebotApi::UnpinAllChatMessages(std::int64_t chatId)
{

}

bool Telebot::TelebotApi::LeaveChat(std::int64_t chatId)
{

}

Telebot::Chat::Ptr Telebot::TelebotApi::GetChat(std::int64_t chatId)
{

}

std::vector<Telebot::ChatMember::Ptr> Telebot::TelebotApi::GetChatAdministrators(std::int64_t chatId)
{

}

std::int32_t Telebot::TelebotApi::GetChatMemberCount(std::int64_t chatId)
{

}

Telebot::ChatMember::Ptr Telebot::TelebotApi::GetChatMember(std::int64_t chatId,
                                                            std::int64_t userId)
{

}

bool Telebot::TelebotApi::SetChatStickerSet(std::int64_t chatId,
                                            const std::string& stickerSetName)
{

}

bool Telebot::TelebotApi::DeleteChatStickerSet(std::int64_t chatId)
{

}

std::vector<Telebot::Sticker::Ptr> Telebot::TelebotApi::GetForumTopicIconStickers()
{

}

Telebot::ForumTopic::Ptr Telebot::TelebotApi::CreateForumTopic(std::int64_t chatId,
                                                               const std::string& name,
                                                               std::int32_t iconColor,
                                                               const std::string& iconCustomEmojiId)
{

}

bool Telebot::TelebotApi::EditForumTopic(std::int64_t chatId,
                                         std::int32_t messageThreadId,
                                         const std::string& name,
                                         std::int8_t iconCustomEmojiId)
{

}

bool Telebot::TelebotApi::CloseForumTopic(std::int64_t chatId,
                                          std::int32_t messageThreadId)
{

}

bool Telebot::TelebotApi::ReopenForumTopic(std::int64_t chatId,
                                           std::int32_t messageThreadId)
{

}

bool Telebot::TelebotApi::DeleteForumTopic(std::int64_t chatId,
                                           std::int32_t messageThreadId)
{

}

bool Telebot::TelebotApi::UnpinAllForumTopicMessages(std::int64_t chatId,
                                                     std::int32_t messageThreadId)
{

}

bool Telebot::TelebotApi::EditGeneralForumTopic(std::int64_t chatId,
                                                const std::string& name)
{

}

bool Telebot::TelebotApi::CloseGeneralForumTopic(std::int64_t chatId)
{

}

bool Telebot::TelebotApi::ReopenGeneralForumTopic(std::int64_t chatId)
{

}

bool Telebot::TelebotApi::HideGeneralForumTopic(std::int64_t chatId)
{

}

bool Telebot::TelebotApi::UnhideGeneralForumTopic(std::int64_t chatId)
{

}

bool Telebot::TelebotApi::AnswerCallbackQuery(const std::string& callbackQueryId,
                                              const std::string& text,
                                              bool showAlert,
                                              const std::string& url,
                                              std::int32_t cacheTime)
{
    Json requestBody;
    requestBody["callback_query_id"] = callbackQueryId;
    if (!text.empty()) requestBody["text"] = text;
    requestBody["show_alert"] = showAlert;
    Json responseBody = Post("answerCallbackQuery", requestBody);

    return responseBody.get<bool>();
}

bool Telebot::TelebotApi::SetMyCommands(const std::vector<BotCommand::Ptr>& commands,
                                        const BotCommandScope::Ptr& scope,
                                        const std::string& languageCode)
{
    Json requestBody;
    requestBody["commands"] = commands;
    if (scope.get() != nullptr) requestBody["scope"] = scope;
    if (!languageCode.empty()) requestBody["language_code"] = languageCode;
    Json responseBody = Post("setMyCommands", requestBody);

    return responseBody.get<bool>();
}

bool Telebot::TelebotApi::DeleteMyCommands(const BotCommandScope::Ptr& scope,
                                           const std::string& languageCode)
{

}

std::vector<Telebot::BotCommand::Ptr> Telebot::TelebotApi::GetMyCommands(const BotCommandScope::Ptr& scope,
                                                                         const std::string& languageCode)
{

}

bool SetMyDescription(const std::string& description,
                      const std::string& languageCode)
{

}

std::string Telebot::TelebotApi::GetMyDescription(const std::string& languageCode)
{

}

bool Telebot::TelebotApi::SetMyShortDescription(const std::string& shortDescription,
                                                const std::string& languageCode)
{

}

std::string Telebot::TelebotApi::GetMyShortDescription(const std::string& languageCode)
{

}

bool Telebot::TelebotApi::SetChatMenuButton(std::int64_t chatId,
                                            const MenuButton::Ptr& menuButton)
{

}

Telebot::MenuButton::Ptr Telebot::TelebotApi::GetChatMenuButton(std::int64_t chatId)
{

}

bool Telebot::TelebotApi::SetMyDefaultAdministratorRights(const ChatAdministratorRights::Ptr& rights,
                                                          bool forChannels)
{

}

Telebot::ChatAdministratorRights::Ptr Telebot::TelebotApi::GetMyDefaultAdministratorRights(bool forChannels)
{

}

Telebot::Message::Ptr Telebot::TelebotApi::EditMessageText(const std::string& text,
                                                           std::int64_t chatId,
                                                           std::int32_t messageId,
                                                           const std::string& inlineMessageId,
                                                           const std::string& parseMode,
                                                           bool disableWebPagePreview,
                                                           const GenericReply::Ptr& replyMarkup,
                                                           const std::vector<MessageEntity::Ptr>& entities)
{
    Json requestBody;
    requestBody["text"] = text;
    requestBody["chat_id"] = chatId;
    requestBody["message_id"] = messageId;
    requestBody["reply_markup"] = replyMarkup;
    Json responseBody = Post("editMessageText", requestBody);

    Message::Ptr message = std::make_shared<Message>();
    *message = responseBody.get<Message>();
    return message;
}

Telebot::Message::Ptr Telebot::TelebotApi::EditMessageCaption(std::int64_t chatId,
                                                              std::int32_t messageId,
                                                              const std::string& caption,
                                                              const std::string& inlineMessageId,
                                                              const GenericReply::Ptr& replyMarkup,
                                                              const std::string& parseMode,
                                                              const std::vector<MessageEntity::Ptr>& captionEntities)
{

}

Telebot::Message::Ptr Telebot::TelebotApi::EditMessageMedia(const InputMedia::Ptr& media,
                                                            const std::int64_t chatId,
                                                            std::int32_t messageId,
                                                            const std::string& inlineMessageId,
                                                            const Telebot::GenericReply::Ptr& replyMarkup)
{

}

Telebot::Message::Ptr Telebot::TelebotApi::EditMessageLiveLocation(float latitude,
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

Telebot::Message::Ptr Telebot::TelebotApi::StopMessageLiveLocation(const std::int64_t chatId,
                                                                   std::int32_t messageId,
                                                                   const std::string& inlineMessageId,
                                                                   const InlineKeyboardMarkup::Ptr& replyMarkup)
{

}

Telebot::Message::Ptr Telebot::TelebotApi::EditMessageReplyMarkup(const std::int64_t chatId,
                                                                  std::int32_t messageId,
                                                                  const std::string& inlineMessageId,
                                                                  const GenericReply::Ptr& replyMarkup)
{

}

Telebot::Poll::Ptr Telebot::TelebotApi::StopPoll(std::int64_t chatId,
                                                 std::int64_t messageId,
                                                 const InlineKeyboardMarkup::Ptr& replyMarkup)
{

}

bool Telebot::TelebotApi::DeleteMessage(std::int64_t chatId,
                                        std::int32_t messageId)
{

}

Telebot::Message::Ptr Telebot::TelebotApi::SendSticker(std::int64_t chatId,
                                                       const InputFile::Ptr& sticker,
                                                       std::int32_t replyToMessageId,
                                                       const GenericReply::Ptr& replyMarkup,
                                                       bool disableNotification,
                                                       bool allowSendingWithoutReply,
                                                       bool protectContent,
                                                       std::int32_t messageThreadId)
{

}

Telebot::StickerSet::Ptr Telebot::TelebotApi::GetStickerSet(const std::string& name)
{

}

std::vector<Telebot::Sticker::Ptr> Telebot::TelebotApi::GetCustomEmojiStickers(const std::vector<std::string>& customEmojiIds)
{

}

Telebot::File::Ptr Telebot::TelebotApi::UploadStickerFile(std::int64_t userId,
                                                          const InputFile::Ptr& pngSticker)
{

}

bool Telebot::TelebotApi::CreateNewStickerSet(std::int64_t userId,
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

bool Telebot::TelebotApi::AddStickerToSet(std::int64_t userId,
                                          const std::string& name,
                                          const std::string& emojis,
                                          const MaskPosition::Ptr& maskPosition,
                                          const InputFile::Ptr& pngSticker,
                                          const InputFile::Ptr& tgsSticker,
                                          const InputFile::Ptr& webmSticker)
{

}

bool Telebot::TelebotApi::SetStickerPositionInSet(const std::string& sticker,
                                                  std::int32_t position)
{

}

bool Telebot::TelebotApi::DeleteStickerFromSet(const std::string& sticker)
{

}

bool Telebot::TelebotApi::SetStickerEmojiList(const std::string& sticker,
                                              const std::vector<std::string>& emojiList)
{

}

bool Telebot::TelebotApi::SetStickerKeywords(const std::string& sticker,
                                             const std::vector<std::string>& keywords)
{

}

bool Telebot::TelebotApi::SetStickerMaskPosition(const std::string& sticker,
                                                 const MaskPosition::Ptr& maskPosition)
{

}

bool Telebot::TelebotApi::SetStickerTitle(const std::string& name,
                                          const std::string& title)
{

}

bool Telebot::TelebotApi::SetStickerSetThumbnail(const std::string& name,
                                                 std::int64_t userId,
                                                 const InputFile::Ptr& thumb)
{

}

bool Telebot::TelebotApi::SetCustomEmojiStickerSetThumbnail(const std::string& name,
                                                            const std::string& customEmojiId)
{

}

bool Telebot::TelebotApi::DeleteStickerSet(const std::string& name)
{

}

bool Telebot::TelebotApi::AnswerInlineQuery(const std::string& inlineQueryId,
                                            const std::vector<InlineQueryResult::Ptr>& results,
                                            std::int32_t cacheTime,
                                            bool isPersonal,
                                            const std::string& nextOffset,
                                            const std::string& switchPmText,
                                            const std::string& switchPmParameter)
{

}

Telebot::SentWebAppMessage::Ptr Telebot::TelebotApi::AnswerWebAppQuery(const std::string& webAppQueryId,
                                                                       const InlineQueryResult::Ptr& result)
{

}

Telebot::Message::Ptr Telebot::TelebotApi::SendInvoice(std::int64_t chatId,
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

std::string Telebot::TelebotApi::CreateInvoiceLink(const std::string& title,
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

bool Telebot::TelebotApi::AnswerShippingQuery(const std::string& shippingQueryId,
                                              bool ok,
                                              const std::vector<ShippingOption::Ptr>& shippingOptions,
                                              const std::string& errorMessage)
{

}

bool Telebot::TelebotApi::AnswerPreCheckoutQuery(const std::string& preCheckoutQueryId,
                                                 bool ok,
                                                 const std::string& errorMessage)
{

}

bool Telebot::TelebotApi::SetPassportDataErrors(std::int64_t userId,
                                                const std::vector<PassportElementError::Ptr>& errors)
{

}

Telebot::Message::Ptr Telebot::TelebotApi::SendGame(std::int64_t chatId,
                                                    const std::string& gameShortName,
                                                    std::int32_t replyToMessageId,
                                                    const InlineKeyboardMarkup::Ptr& replyMarkup,
                                                    bool disableNotification,
                                                    bool allowSendingWithoutReply,
                                                    bool protectContent,
                                                    std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::TelebotApi::SetGameScore(std::int64_t userId,
                                                        std::int32_t score,
                                                        bool force,
                                                        bool disableEditMessage,
                                                        std::int64_t chatId,
                                                        std::int32_t messageId,
                                                        const std::string& inlineMessageId)
{

}

std::vector<Telebot::GameHighScore::Ptr> Telebot::TelebotApi::GetGameHighScores(std::int64_t userId,
                                                                                std::int64_t chatId,
                                                                                std::int32_t messageId,
                                                                                const std::string& inlineMessageId)
{

}