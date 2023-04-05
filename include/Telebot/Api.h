#ifndef Telebot_ControllerH
#define Telebot_ControllerH

#include <boost/variant.hpp>
#include <json.hpp>

#include "HttpsClient.h"
#include "Types/Update.h"
#include "Types/InputFile.h"
#include "Types/WebhookInfo.h"
#include "Types/MessageId.h"
#include "Types/InputMedia.h"
#include "Types/UserProfilePhotos.h"
#include "Types/ForumTopic.h"
#include "Types/BotCommand.h"
#include "Types/BotCommandScope.h"
#include "Types/MenuButton.h"
#include "Types/ChatAdministratorRights.h"
#include "Types/StickerSet.h"
#include "Types/InlineQueryResult.h"
#include "Types/SentWebAppMessage.h"
#include "Types/LabeledPrice.h"
#include "Types/ShippingOption.h"
#include "Types/PassportElementError.h"
#include "Types/GameHighScore.h"

typedef nlohmann::json Json;

namespace Telebot
{
    class Api
    {
    private:
        static const std::string HOST;
        static const unsigned int HTTP_VERSION;

        template<typename T>
        std::shared_ptr<T> Get(const std::string& methodName)
        {
            std::shared_ptr<Telebot::HttpContext> httpContext = std::make_shared<Telebot::HttpContext>();
            httpContext->Request->method_string("GET");
            httpContext->Request->set(boost::beast::http::field::host, HOST);
            httpContext->Request->target("/bot" + _token + "/" + methodName);
            httpContext->Request->version(HTTP_VERSION);

            _client->SendHttps(httpContext);

            Json json = Json::parse(httpContext->Response->body());
            if (json.at("ok").get<bool>()) return std::make_shared<T>(json.at("result"));
        }

    public:
        std::string _token;
        std::unique_ptr<HttpsClient> _client;

        explicit Api(const std::string& token);
        ~Api() = default;

        std::vector<Update::Ptr> GetUpdates(std::int32_t offset = 0,
                                            std::int32_t limit = 100,
                                            std::int32_t timeout = 0,
                                            const std::vector<std::string>& allowedUpdates = std::vector<std::string>());

        bool SetWebhook(const std::string& url,
                        const InputFile::Ptr& certificate = nullptr,
                        std::int32_t maxConnections = 40,
                        const std::vector<std::string>& allowedUpdates = std::vector<std::string>(),
                        const std::string& ipAddress = "",
                        bool dropPendingUpdates = false,
                        const std::string& secretToken = "");

        bool DeleteWebhook(bool dropPendingUpdates = false);

        WebhookInfo::Ptr GetWebhookInfo();

        User::Ptr GetMe();

        bool LogOut();

        bool Close();

        Message::Ptr SendMessage(const boost::variant<std::int64_t, std::string>& chatId,
                                 const std::string& text,
                                 bool disableWebPagePreview = false,
                                 std::int32_t replyToMessageId = 0,
                                 const GenericReply::Ptr& replyMarkup = nullptr,
                                 const std::string& parseMode = "",
                                 bool disableNotification = false,
                                 const std::vector<MessageEntity::Ptr>& entities = std::vector<MessageEntity::Ptr>(),
                                 bool allowSendingWithoutReply = false,
                                 bool protectContent = false,
                                 std::int32_t messageThreadId = 0);

        Message::Ptr ForwardMessage(const boost::variant<std::int64_t, std::string>& chatId,
                                    const boost::variant<std::int64_t, std::string>& fromChatId,
                                    std::int32_t messageId,
                                    bool disableNotification = false,
                                    bool protectContent = false,
                                    std::int32_t messageThreadId = 0);

        MessageId::Ptr CopyMessage(const boost::variant<std::int64_t, std::string>& chatId,
                                   const boost::variant<std::int64_t, std::string>& fromChatId,
                                   std::int32_t messageId,
                                   const std::string& caption = "",
                                   const std::string& parseMode = "",
                                   const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                                   bool disableNotification = false,
                                   std::int32_t replyToMessageId = 0,
                                   bool allowSendingWithoutReply = false,
                                   const GenericReply::Ptr& replyMarkup = std::make_shared<GenericReply>(),
                                   bool protectContent = false,
                                   std::int32_t messageThreadId = 0);

        Message::Ptr SendPhoto(const boost::variant<std::int64_t, std::string>& chatId,
                               const boost::variant<InputFile::Ptr, std::string>& photo,
                               const std::string& caption = "",
                               std::int32_t replyToMessageId = 0,
                               const GenericReply::Ptr& replyMarkup = nullptr,
                               const std::string& parseMode = "",
                               bool disableNotification = false,
                               const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                               bool allowSendingWithoutReply = false,
                               bool protectContent = false,
                               std::int32_t messageThreadId = 0,
                               bool hasSpoiler = false);

        Message::Ptr SendAudio(const boost::variant<std::int64_t, std::string>& chatId,
                               const boost::variant<InputFile::Ptr, std::string>& audio,
                               const std::string& caption = "",
                               std::int32_t duration = 0,
                               const std::string& performer = "",
                               const std::string& title = "",
                               const boost::variant<InputFile::Ptr, std::string>& thumb = "",
                               std::int32_t replyToMessageId = 0,
                               const GenericReply::Ptr& replyMarkup = nullptr,
                               const std::string& parseMode = "",
                               bool disableNotification = false,
                               const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                               bool allowSendingWithoutReply = false,
                               bool protectContent = false,
                               std::int32_t messageThreadId = 0);

        Message::Ptr SendDocument(const boost::variant<std::int64_t, std::string>& chatId,
                                  const boost::variant<InputFile::Ptr, std::string>& document,
                                  const boost::variant<InputFile::Ptr, std::string>& thumb = "",
                                  const std::string& caption = "",
                                  std::int32_t replyToMessageId = 0,
                                  const GenericReply::Ptr& replyMarkup = nullptr,
                                  const std::string& parseMode = "",
                                  bool disableNotification = false,
                                  const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                                  bool disableContentTypeDetection = false,
                                  bool allowSendingWithoutReply = false,
                                  bool protectContent = false,
                                  std::int32_t messageThreadId = 0);

        Message::Ptr SendVideo(const boost::variant<std::int64_t, std::string>& chatId,
                               const boost::variant<InputFile::Ptr, std::string>& video,
                               bool supportsStreaming = false,
                               std::int32_t duration = 0,
                               std::int32_t width = 0,
                               std::int32_t height = 0,
                               const boost::variant<InputFile::Ptr, std::string>& thumb = "",
                               const std::string& caption = "",
                               std::int32_t replyToMessageId = 0,
                               const GenericReply::Ptr& replyMarkup = nullptr,
                               const std::string& parseMode = "",
                               bool disableNotification = false,
                               const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                               bool allowSendingWithoutReply = false,
                               bool protectContent = false,
                               std::int32_t messageThreadId = 0,
                               bool hasSpoiler = false);

        Message::Ptr SendAnimation(const boost::variant<std::int64_t, std::string>& chatId,
                                   const boost::variant<InputFile::Ptr, std::string>& animation,
                                   std::int32_t duration = 0,
                                   std::int32_t width = 0,
                                   std::int32_t height = 0,
                                   const boost::variant<InputFile::Ptr, std::string>& thumb = "",
                                   const std::string& caption = "",
                                   std::int32_t replyToMessageId = 0,
                                   const GenericReply::Ptr& replyMarkup = nullptr,
                                   const std::string& parseMode = "",
                                   bool disableNotification = false,
                                   const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                                   bool allowSendingWithoutReply = false,
                                   bool protectContent = false,
                                   std::int32_t messageThreadId = 0,
                                   bool hasSpoiler = false);

        Message::Ptr SendVoice(const boost::variant<std::int64_t, std::string>& chatId,
                               const boost::variant<InputFile::Ptr, std::string>& voice,
                               const std::string& caption = "",
                               std::int32_t duration = 0,
                               std::int32_t replyToMessageId = 0,
                               const GenericReply::Ptr& replyMarkup = nullptr,
                               const std::string& parseMode = "",
                               bool disableNotification = false,
                               const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                               bool allowSendingWithoutReply = false,
                               bool protectContent = false,
                               std::int32_t messageThreadId = 0);

        Message::Ptr SendVideoNote(const boost::variant<std::int64_t, std::string>& chatId,
                                   const boost::variant<InputFile::Ptr, std::string>& videoNote,
                                   std::int64_t replyToMessageId = 0,
                                   bool disableNotification = false,
                                   std::int32_t duration = 0,
                                   std::int32_t length = 0,
                                   const boost::variant<InputFile::Ptr, std::string>& thumb = "",
                                   const GenericReply::Ptr& replyMarkup = nullptr,
                                   bool allowSendingWithoutReply = false,
                                   bool protectContent = false,
                                   std::int32_t messageThreadId = 0);

        std::vector<Message::Ptr> SendMediaGroup(const boost::variant<std::int64_t, std::string>& chatId,
                                                 const std::vector<InputMedia::Ptr>& media,
                                                 bool disableNotification = false,
                                                 std::int32_t replyToMessageId = 0,
                                                 bool allowSendingWithoutReply = false,
                                                 bool protectContent = false,
                                                 std::int32_t messageThreadId = 0);

        Message::Ptr SendLocation(const boost::variant<std::int64_t, std::string>& chatId,
                                  float latitude,
                                  float longitude,
                                  std::int32_t livePeriod = 0,
                                  std::int32_t replyToMessageId = 0,
                                  const GenericReply::Ptr& replyMarkup = nullptr,
                                  bool disableNotification = false,
                                  float horizontalAccuracy = 0,
                                  std::int32_t heading = 0,
                                  std::int32_t proximityAlertRadius = 0,
                                  bool allowSendingWithoutReply = false,
                                  bool protectContent = false,
                                  std::int32_t messageThreadId = 0);

        Message::Ptr SendVenue(const boost::variant<std::int64_t, std::string>& chatId,
                               float latitude,
                               float longitude,
                               const std::string& title,
                               const std::string& address,
                               const std::string& foursquareId = "",
                               const std::string& foursquareType = "",
                               bool disableNotification = false,
                               std::int32_t replyToMessageId = 0,
                               const GenericReply::Ptr& replyMarkup = nullptr,
                               const std::string& googlePlaceId = "",
                               const std::string& googlePlaceType = "",
                               bool allowSendingWithoutReply = false,
                               bool protectContent = false,
                               std::int32_t messageThreadId = 0);

        Message::Ptr SendContact(const boost::variant<std::int64_t, std::string>& chatId,
                                 const std::string& phoneNumber,
                                 const std::string& firstName,
                                 const std::string& lastName = "",
                                 const std::string& vcard = "",
                                 bool disableNotification = false,
                                 std::int32_t replyToMessageId = 0,
                                 const GenericReply::Ptr& replyMarkup = nullptr,
                                 bool allowSendingWithoutReply = false,
                                 bool protectContent = false,
                                 std::int32_t messageThreadId = 0);

        Message::Ptr SendPoll(const boost::variant<std::int64_t, std::string>& chatId,
                              const std::string& question,
                              const std::vector<std::string>& options,
                              bool disableNotification = false,
                              std::int32_t replyToMessageId = 0,
                              const GenericReply::Ptr& replyMarkup = nullptr,
                              bool isAnonymous = true,
                              const std::string& type = "",
                              bool allowsMultipleAnswers = false,
                              std::int32_t correctOptionId = -1,
                              const std::string& explanation = "",
                              const std::string& explanationParseMode = "",
                              const std::vector<MessageEntity::Ptr>& explanationEntities = std::vector<MessageEntity::Ptr>(),
                              std::int32_t openPeriod = 0,
                              std::int32_t closeDate = 0,
                              bool isClosed = false,
                              bool allowSendingWithoutReply = false,
                              bool protectContent = false,
                              std::int32_t messageThreadId = 0);

        Message::Ptr SendDice(const boost::variant<std::int64_t, std::string>& chatId,
                              bool disableNotification = false,
                              std::int32_t replyToMessageId = 0,
                              const GenericReply::Ptr& replyMarkup = nullptr,
                              const std::string& emoji = "",
                              bool allowSendingWithoutReply = false,
                              bool protectContent = false,
                              std::int32_t messageThreadId = 0);

        bool SendChatAction(std::int64_t chatId,
                            const std::string& action,
                            std::int32_t messageThreadId = 0);

        UserProfilePhotos::Ptr GetUserProfilePhotos(std::int64_t userId,
                                                    std::int32_t offset = 0,
                                                    std::int32_t limit = 100);

        File::Ptr GetFile(const std::string& fileId);

        bool BanChatMember(const boost::variant<std::int64_t, std::string>& chatId,
                           std::int64_t userId,
                           std::int32_t untilDate = 0,
                           bool revokeMessages = true);

        bool UnbanChatMember(const boost::variant<std::int64_t, std::string>& chatId,
                             std::int64_t userId,
                             bool onlyIfBanned = false);

        bool RestrictChatMember(const boost::variant<std::int64_t, std::string>& chatId,
                                std::int64_t userId,
                                const ChatPermissions::Ptr& permissions,
                                std::int64_t untilDate = 0,
                                bool useIndependentChatPermissions = false);

        bool PromoteChatMember(const boost::variant<std::int64_t, std::string>& chatId,
                               std::int64_t userId,
                               bool canChangeInfo = false,
                               bool canPostMessages = false,
                               bool canEditMessages = false,
                               bool canDeleteMessages = false,
                               bool canInviteUsers = false,
                               bool canPinMessages = false,
                               bool canPromoteMembers = false,
                               bool isAnonymous = false,
                               bool canManageChat = false,
                               bool canManageVideoChats = false,
                               bool canRestrictMembers = false,
                               bool canManageTopics = false);

        bool SetChatAdministratorCustomTitle(const boost::variant<std::int64_t, std::string>& chatId,
                                             std::int64_t userId,
                                             const std::string& customTitle);

        bool BanChatSenderChat(const boost::variant<std::int64_t, std::string>& chatId,
                               std::int64_t senderChatId);

        bool UnbanChatSenderChat(const boost::variant<std::int64_t, std::string>& chatId,
                                 std::int64_t senderChatId);

        bool SetChatPermissions(const boost::variant<std::int64_t, std::string>& chatId,
                                const ChatPermissions::Ptr& permissions,
                                bool useIndependentChatPermissions = false);

        std::string ExportChatInviteLink(const boost::variant<std::int64_t, std::string>& chatId);

        ChatInviteLink::Ptr CreateChatInviteLink(const boost::variant<std::int64_t, std::string>& chatId,
                                                 std::int32_t expireDate = 0,
                                                 std::int32_t memberLimit = 0,
                                                 const std::string& name = "",
                                                 bool createsJoinRequest = false);

        ChatInviteLink::Ptr EditChatInviteLink(const boost::variant<std::int64_t, std::string>& chatId,
                                               const std::string& inviteLink,
                                               std::int32_t expireDate = 0,
                                               std::int32_t memberLimit = 0,
                                               const std::string& name = "",
                                               bool createsJoinRequest = false);

        ChatInviteLink::Ptr RevokeChatInviteLink(const boost::variant<std::int64_t, std::string>& chatId,
                                                 const std::string& inviteLink);

        bool ApproveChatJoinRequest(const boost::variant<std::int64_t, std::string>& chatId,
                                    std::int64_t userId);

        bool DeclineChatJoinRequest(const boost::variant<std::int64_t, std::string>& chatId,
                                    std::int64_t userId);

        bool SetChatPhoto(const boost::variant<std::int64_t, std::string>& chatId,
                          const InputFile::Ptr& photo);

        bool DeleteChatPhoto(const boost::variant<std::int64_t, std::string>& chatId);

        bool SetChatTitle(const boost::variant<std::int64_t, std::string>& chatId,
                          const std::string& title);

        bool SetChatDescription(const boost::variant<std::int64_t, std::string>& chatId,
                                const std::string& description = "");

        bool PinChatMessage(const boost::variant<std::int64_t, std::string>& chatId,
                            std::int32_t messageId,
                            bool disableNotification = false);

        bool UnpinChatMessage(const boost::variant<std::int64_t, std::string>& chatId,
                              std::int32_t messageId = 0);

        bool UnpinAllChatMessages(const boost::variant<std::int64_t, std::string>& chatId);

        bool LeaveChat(const boost::variant<std::int64_t, std::string>& chatId);

        Chat::Ptr GetChat(const boost::variant<std::int64_t, std::string>& chatId);

        std::vector<ChatMember::Ptr> GetChatAdministrators(const boost::variant<std::int64_t, std::string>& chatId);

        std::int32_t GetChatMemberCount(const boost::variant<std::int64_t, std::string>& chatId);

        ChatMember::Ptr GetChatMember(const boost::variant<std::int64_t, std::string>& chatId,
                                      std::int64_t userId);

        bool SetChatStickerSet(const boost::variant<std::int64_t, std::string>& chatId,
                               const std::string& stickerSetName);

        bool DeleteChatStickerSet(const boost::variant<std::int64_t, std::string>& chatId);

        std::vector<Sticker::Ptr> GetForumTopicIconStickers();

        ForumTopic::Ptr CreateForumTopic(const boost::variant<std::int64_t, std::string>& chatId,
                                         const std::string& name,
                                         std::int32_t iconColor = 0,
                                         const std::string& iconCustomEmojiId = "");

        bool EditForumTopic(const boost::variant<std::int64_t, std::string>& chatId,
                            std::int32_t messageThreadId,
                            const std::string& name = "",
                            const boost::variant<std::int8_t, std::string>& iconCustomEmojiId = 0);

        bool CloseForumTopic(const boost::variant<std::int64_t, std::string>& chatId,
                             std::int32_t messageThreadId);

        bool ReopenForumTopic(const boost::variant<std::int64_t, std::string>& chatId,
                              std::int32_t messageThreadId);

        bool DeleteForumTopic(const boost::variant<std::int64_t, std::string>& chatId,
                              std::int32_t messageThreadId);

        bool UnpinAllForumTopicMessages(const boost::variant<std::int64_t, std::string>& chatId,
                                        std::int32_t messageThreadId);

        bool EditGeneralForumTopic(const boost::variant<std::int64_t, std::string>& chatId,
                                   const std::string& name);

        bool CloseGeneralForumTopic(const boost::variant<std::int64_t, std::string>& chatId);

        bool ReopenGeneralForumTopic(const boost::variant<std::int64_t, std::string>& chatId);

        bool HideGeneralForumTopic(const boost::variant<std::int64_t, std::string>& chatId);

        bool UnhideGeneralForumTopic(const boost::variant<std::int64_t, std::string>& chatId);

        bool AnswerCallbackQuery(const std::string& callbackQueryId,
                                 const std::string& text = "",
                                 bool showAlert = false,
                                 const std::string& url = "",
                                 std::int32_t cacheTime = 0);

        bool SetMyCommands(const std::vector<BotCommand::Ptr>& commands,
                           const BotCommandScope::Ptr& scope = nullptr,
                           const std::string& languageCode = "");

        bool DeleteMyCommands(const BotCommandScope::Ptr& scope = nullptr,
                              const std::string& languageCode = "");

        std::vector<BotCommand::Ptr> GetMyCommands(const BotCommandScope::Ptr& scope = nullptr,
                                                   const std::string& languageCode = "");

        bool SetMyDescription(const std::string& description = "",
                              const std::string& languageCode = "");

        std::string GetMyDescription(const std::string& languageCode = "");

        bool SetMyShortDescription(const std::string& shortDescription = "",
                                   const std::string& languageCode = "");

        std::string GetMyShortDescription(const std::string& languageCode = "");

        bool SetChatMenuButton(std::int64_t chatId = 0,
                               const MenuButton::Ptr& menuButton = nullptr);

        MenuButton::Ptr GetChatMenuButton(std::int64_t chatId = 0);

        bool SetMyDefaultAdministratorRights(const ChatAdministratorRights::Ptr& rights = nullptr,
                                             bool forChannels = false);

        ChatAdministratorRights::Ptr GetMyDefaultAdministratorRights(bool forChannels = false);

        Message::Ptr EditMessageText(const std::string& text,
                                     const boost::variant<std::int64_t, std::string>& chatId = 0,
                                     std::int32_t messageId = 0,
                                     const std::string& inlineMessageId = "",
                                     const std::string& parseMode = "",
                                     bool disableWebPagePreview = false,
                                     const GenericReply::Ptr& replyMarkup = nullptr,
                                     const std::vector<MessageEntity::Ptr>& entities = std::vector<MessageEntity::Ptr>());

        Message::Ptr EditMessageCaption(const boost::variant<std::int64_t, std::string>& chatId = 0,
                                        std::int32_t messageId = 0,
                                        const std::string& caption = "",
                                        const std::string& inlineMessageId = "",
                                        const GenericReply::Ptr& replyMarkup = nullptr,
                                        const std::string& parseMode = "",
                                        const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>());

        Message::Ptr EditMessageMedia(const InputMedia::Ptr& media,
                                      const boost::variant<std::int64_t, std::string>& chatId = 0,
                                      std::int32_t messageId = 0,
                                      const std::string& inlineMessageId = "",
                                      const GenericReply::Ptr& replyMarkup = nullptr);

        Message::Ptr EditMessageLiveLocation(float latitude,
                                             float longitude,
                                             const boost::variant<std::int64_t, std::string>& chatId = "",
                                             std::int32_t messageId = 0,
                                             const std::string& inlineMessageId = "",
                                             const InlineKeyboardMarkup::Ptr& replyMarkup = std::make_shared<InlineKeyboardMarkup>(),
                                             float horizontalAccuracy = 0,
                                             std::int32_t heading = 0,
                                             std::int32_t proximityAlertRadius = 0);

        Message::Ptr StopMessageLiveLocation(const boost::variant<std::int64_t, std::string>& chatId = "",
                                             std::int32_t messageId = 0,
                                             const std::string& inlineMessageId = "",
                                             const InlineKeyboardMarkup::Ptr& replyMarkup = std::make_shared<InlineKeyboardMarkup>());

        Message::Ptr EditMessageReplyMarkup(const boost::variant<std::int64_t, std::string>& chatId = 0,
                                            std::int32_t messageId = 0,
                                            const std::string& inlineMessageId = "",
                                            const GenericReply::Ptr& replyMarkup = nullptr);

        Poll::Ptr StopPoll(const boost::variant<std::int64_t, std::string>& chatId,
                           std::int64_t messageId,
                           const InlineKeyboardMarkup::Ptr& replyMarkup = std::make_shared<InlineKeyboardMarkup>());

        bool DeleteMessage(const boost::variant<std::int64_t, std::string>& chatId,
                           std::int32_t messageId);

        Message::Ptr SendSticker(const boost::variant<std::int64_t, std::string>& chatId,
                                 const boost::variant<InputFile::Ptr, std::string>& sticker,
                                 std::int32_t replyToMessageId = 0,
                                 const GenericReply::Ptr& replyMarkup = nullptr,
                                 bool disableNotification = false,
                                 bool allowSendingWithoutReply = false,
                                 bool protectContent = false,
                                 std::int32_t messageThreadId = 0);

        StickerSet::Ptr GetStickerSet(const std::string& name);

        std::vector<Sticker::Ptr> GetCustomEmojiStickers(const std::vector<std::string>& customEmojiIds);

        File::Ptr UploadStickerFile(std::int64_t userId,
                                    const InputFile::Ptr& pngSticker);

        bool CreateNewStickerSet(std::int64_t userId,
                                 const std::string& name,
                                 const std::string& title,
                                 const std::string& emojis,
                                 const MaskPosition::Ptr& maskPosition = nullptr,
                                 const boost::variant<InputFile::Ptr, std::string>& pngSticker = "",
                                 const InputFile::Ptr& tgsSticker = nullptr,
                                 const InputFile::Ptr& webmSticker = nullptr,
                                 const std::string& stickerType = "");

        bool AddStickerToSet(std::int64_t userId,
                             const std::string& name,
                             const std::string& emojis,
                             const MaskPosition::Ptr& maskPosition = nullptr,
                             const boost::variant<InputFile::Ptr, std::string>& pngSticker = "",
                             const InputFile::Ptr& tgsSticker = nullptr,
                             const InputFile::Ptr& webmSticker = nullptr);

        bool SetStickerPositionInSet(const std::string& sticker,
                                     std::int32_t position);

        bool DeleteStickerFromSet(const std::string& sticker);

        bool SetStickerEmojiList(const std::string& sticker,
                                 const std::vector<std::string>& emojiList);

        bool SetStickerKeywords(const std::string& sticker,
                                const std::vector<std::string>& keywords);

        bool SetStickerMaskPosition(const std::string& sticker,
                                    const MaskPosition::Ptr& maskPosition = nullptr);

        bool SetStickerTitle(const std::string& name,
                             const std::string& title);

        bool SetStickerSetThumbnail(const std::string& name,
                                    std::int64_t userId,
                                    const boost::variant<InputFile::Ptr, std::string>& thumb = "");

        bool SetCustomEmojiStickerSetThumbnail(const std::string& name,
                                               const std::string& customEmojiId = "");

        bool DeleteStickerSet(const std::string& name);

        bool AnswerInlineQuery(const std::string& inlineQueryId,
                               const std::vector<InlineQueryResult::Ptr>& results,
                               std::int32_t cacheTime = 300,
                               bool isPersonal = false,
                               const std::string& nextOffset = "",
                               const std::string& switchPmText = "",
                               const std::string& switchPmParameter = "");

        SentWebAppMessage::Ptr AnswerWebAppQuery(const std::string& webAppQueryId,
                                                 const InlineQueryResult::Ptr& result);

        Message::Ptr SendInvoice(const boost::variant<std::int64_t, std::string>& chatId,
                                 const std::string& title,
                                 const std::string& description,
                                 const std::string& payload,
                                 const std::string& providerToken,
                                 const std::string& currency,
                                 const std::vector<LabeledPrice::Ptr>& prices,
                                 const std::string& providerData = "",
                                 const std::string& photoUrl = "",
                                 std::int32_t photoSize = 0,
                                 std::int32_t photoWidth = 0,
                                 std::int32_t photoHeight = 0,
                                 bool needName = false,
                                 bool needPhoneNumber = false,
                                 bool needEmail = false,
                                 bool needShippingAddress = false,
                                 bool sendPhoneNumberToProvider = false,
                                 bool sendEmailToProvider = false,
                                 bool isFlexible = false,
                                 std::int32_t replyToMessageId = 0,
                                 const GenericReply::Ptr& replyMarkup = nullptr,
                                 bool disableNotification = false,
                                 bool allowSendingWithoutReply = false,
                                 std::int32_t maxTipAmount = 0,
                                 const std::vector<std::int32_t>& suggestedTipAmounts = std::vector<std::int32_t>(),
                                 const std::string& startParameter = "",
                                 bool protectContent = false,
                                 std::int32_t messageThreadId = 0);

        std::string CreateInvoiceLink(const std::string& title,
                                      const std::string& description,
                                      const std::string& payload,
                                      const std::string& providerToken,
                                      const std::string& currency,
                                      const std::vector<LabeledPrice::Ptr>& prices,
                                      std::int32_t maxTipAmount = 0,
                                      const std::vector<std::int32_t>& suggestedTipAmounts = std::vector<std::int32_t>(),
                                      const std::string& providerData = "",
                                      const std::string& photoUrl = "",
                                      std::int32_t photoSize = 0,
                                      std::int32_t photoWidth = 0,
                                      std::int32_t photoHeight = 0,
                                      bool needName = false,
                                      bool needPhoneNumber = false,
                                      bool needEmail = false,
                                      bool needShippingAddress = false,
                                      bool sendPhoneNumberToProvider = false,
                                      bool sendEmailToProvider = false,
                                      bool isFlexible = false);

        bool AnswerShippingQuery(const std::string& shippingQueryId,
                                 bool ok,
                                 const std::vector<ShippingOption::Ptr>& shippingOptions = std::vector<ShippingOption::Ptr>(),
                                 const std::string& errorMessage = "");

        bool AnswerPreCheckoutQuery(const std::string& preCheckoutQueryId,
                                    bool ok,
                                    const std::string& errorMessage = "");

        bool SetPassportDataErrors(std::int64_t userId,
                                   const std::vector<PassportElementError::Ptr>& errors);

        Message::Ptr SendGame(std::int64_t chatId,
                              const std::string& gameShortName,
                              std::int32_t replyToMessageId = 0,
                              const InlineKeyboardMarkup::Ptr& replyMarkup = std::make_shared<InlineKeyboardMarkup>(),
                              bool disableNotification = false,
                              bool allowSendingWithoutReply = false,
                              bool protectContent = false,
                              std::int32_t messageThreadId = 0);

        Message::Ptr SetGameScore(std::int64_t userId,
                                  std::int32_t score,
                                  bool force = false,
                                  bool disableEditMessage = false,
                                  std::int64_t chatId = 0,
                                  std::int32_t messageId = 0,
                                  const std::string& inlineMessageId = "");

        std::vector<GameHighScore::Ptr> GetGameHighScores(std::int64_t userId,
                                                          std::int64_t chatId = 0,
                                                          std::int32_t messageId = 0,
                                                          const std::string& inlineMessageId = "");
    };
}

#endif