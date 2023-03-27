#ifndef Telebot_ControllerH
#define Telebot_ControllerH

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/variant.hpp>

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

namespace Telebot
{
    class Api
    {
    public:
        Api() = default;
        ~Api() = default;

        std::vector<Update::Ptr> GetUpdates(std::int32_t offset = 0,
                                            std::int32_t limit = 100,
                                            std::int32_t timeout = 0,
                                            const std::vector<std::string>& allowedUpdates = std::vector<std::string>());

        bool SetWebhook(const std::string& url,
                        InputFile::Ptr certificate = nullptr,
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

        Message::Ptr SendMessage(boost::variant<std::int64_t, std::string> chatId,
                                 const std::string& text,
                                 bool disableWebPagePreview = false,
                                 std::int32_t replyToMessageId = 0,
                                 GenericReply::Ptr replyMarkup = nullptr,
                                 const std::string& parseMode = "",
                                 bool disableNotification = false,
                                 const std::vector<MessageEntity::Ptr>& entities = std::vector<MessageEntity::Ptr>(),
                                 bool allowSendingWithoutReply = false,
                                 bool protectContent = false,
                                 std::int32_t messageThreadId = 0);

        Message::Ptr ForwardMessage(boost::variant<std::int64_t, std::string> chatId,
                                    boost::variant<std::int64_t, std::string> fromChatId,
                                    std::int32_t messageId,
                                    bool disableNotification = false,
                                    bool protectContent = false,
                                    std::int32_t messageThreadId = 0);

        MessageId::Ptr CopyMessage(boost::variant<std::int64_t, std::string> chatId,
                                   boost::variant<std::int64_t, std::string> fromChatId,
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

        Message::Ptr SendPhoto(boost::variant<std::int64_t, std::string> chatId,
                               boost::variant<InputFile::Ptr, std::string> photo,
                               const std::string& caption = "",
                               std::int32_t replyToMessageId = 0,
                               GenericReply::Ptr replyMarkup = nullptr,
                               const std::string& parseMode = "",
                               bool disableNotification = false,
                               const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                               bool allowSendingWithoutReply = false,
                               bool protectContent = false,
                               std::int32_t messageThreadId = 0,
                               bool hasSpoiler = false);

        Message::Ptr SendAudio(boost::variant<std::int64_t, std::string> chatId,
                               boost::variant<InputFile::Ptr, std::string> audio,
                               const std::string& caption = "",
                               std::int32_t duration = 0,
                               const std::string& performer = "",
                               const std::string& title = "",
                               boost::variant<InputFile::Ptr, std::string> thumb = "",
                               std::int32_t replyToMessageId = 0,
                               GenericReply::Ptr replyMarkup = nullptr,
                               const std::string& parseMode = "",
                               bool disableNotification = false,
                               const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                               bool allowSendingWithoutReply = false,
                               bool protectContent = false,
                               std::int32_t messageThreadId = 0);

        Message::Ptr SendDocument(boost::variant<std::int64_t, std::string> chatId,
                                  boost::variant<InputFile::Ptr, std::string> document,
                                  boost::variant<InputFile::Ptr, std::string> thumb = "",
                                  const std::string& caption = "",
                                  std::int32_t replyToMessageId = 0,
                                  GenericReply::Ptr replyMarkup = nullptr,
                                  const std::string& parseMode = "",
                                  bool disableNotification = false,
                                  const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                                  bool disableContentTypeDetection = false,
                                  bool allowSendingWithoutReply = false,
                                  bool protectContent = false,
                                  std::int32_t messageThreadId = 0);

        Message::Ptr SendVideo(boost::variant<std::int64_t, std::string> chatId,
                               boost::variant<InputFile::Ptr, std::string> video,
                               bool supportsStreaming = false,
                               std::int32_t duration = 0,
                               std::int32_t width = 0,
                               std::int32_t height = 0,
                               boost::variant<InputFile::Ptr, std::string> thumb = "",
                               const std::string& caption = "",
                               std::int32_t replyToMessageId = 0,
                               GenericReply::Ptr replyMarkup = nullptr,
                               const std::string& parseMode = "",
                               bool disableNotification = false,
                               const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                               bool allowSendingWithoutReply = false,
                               bool protectContent = false,
                               std::int32_t messageThreadId = 0,
                               bool hasSpoiler = false);

        Message::Ptr SendAnimation(boost::variant<std::int64_t, std::string> chatId,
                                   boost::variant<InputFile::Ptr, std::string> animation,
                                   std::int32_t duration = 0,
                                   std::int32_t width = 0,
                                   std::int32_t height = 0,
                                   boost::variant<InputFile::Ptr, std::string> thumb = "",
                                   const std::string& caption = "",
                                   std::int32_t replyToMessageId = 0,
                                   GenericReply::Ptr replyMarkup = nullptr,
                                   const std::string& parseMode = "",
                                   bool disableNotification = false,
                                   const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                                   bool allowSendingWithoutReply = false,
                                   bool protectContent = false,
                                   std::int32_t messageThreadId = 0,
                                   bool hasSpoiler = false);

        Message::Ptr SendVoice(boost::variant<std::int64_t, std::string> chatId,
                               boost::variant<InputFile::Ptr, std::string> voice,
                               const std::string& caption = "",
                               std::int32_t duration = 0,
                               std::int32_t replyToMessageId = 0,
                               GenericReply::Ptr replyMarkup = nullptr,
                               const std::string& parseMode = "",
                               bool disableNotification = false,
                               const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>(),
                               bool allowSendingWithoutReply = false,
                               bool protectContent = false,
                               std::int32_t messageThreadId = 0);

        Message::Ptr SendVideoNote(boost::variant<std::int64_t, std::string> chatId,
                                   boost::variant<InputFile::Ptr, std::string> videoNote,
                                   std::int64_t replyToMessageId = 0,
                                   bool disableNotification = false,
                                   std::int32_t duration = 0,
                                   std::int32_t length = 0,
                                   boost::variant<InputFile::Ptr, std::string> thumb = "",
                                   GenericReply::Ptr replyMarkup = nullptr,
                                   bool allowSendingWithoutReply = false,
                                   bool protectContent = false,
                                   std::int32_t messageThreadId = 0);

        std::vector<Message::Ptr> SendMediaGroup(boost::variant<std::int64_t, std::string> chatId,
                                                 const std::vector<InputMedia::Ptr>& media,
                                                 bool disableNotification = false,
                                                 std::int32_t replyToMessageId = 0,
                                                 bool allowSendingWithoutReply = false,
                                                 bool protectContent = false,
                                                 std::int32_t messageThreadId = 0);

        Message::Ptr SendLocation(boost::variant<std::int64_t, std::string> chatId,
                                  float latitude,
                                  float longitude,
                                  std::int32_t livePeriod = 0,
                                  std::int32_t replyToMessageId = 0,
                                  GenericReply::Ptr replyMarkup = nullptr,
                                  bool disableNotification = false,
                                  float horizontalAccuracy = 0,
                                  std::int32_t heading = 0,
                                  std::int32_t proximityAlertRadius = 0,
                                  bool allowSendingWithoutReply = false,
                                  bool protectContent = false,
                                  std::int32_t messageThreadId = 0);

        Message::Ptr EditMessageLiveLocation(float latitude,
                                             float longitude,
                                             boost::variant<std::int64_t, std::string> chatId = "",
                                             std::int32_t messageId = 0,
                                             const std::string& inlineMessageId = "",
                                             InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>(),
                                             float horizontalAccuracy = 0,
                                             std::int32_t heading = 0,
                                             std::int32_t proximityAlertRadius = 0);

        Message::Ptr StopMessageLiveLocation(boost::variant<std::int64_t, std::string> chatId = "",
                                             std::int32_t messageId = 0,
                                             const std::string& inlineMessageId = "",
                                             InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>());

        Message::Ptr SendVenue(boost::variant<std::int64_t, std::string> chatId,
                               float latitude,
                               float longitude,
                               const std::string& title,
                               const std::string& address,
                               const std::string& foursquareId = "",
                               const std::string& foursquareType = "",
                               bool disableNotification = false,
                               std::int32_t replyToMessageId = 0,
                               GenericReply::Ptr replyMarkup = nullptr,
                               const std::string& googlePlaceId = "",
                               const std::string& googlePlaceType = "",
                               bool allowSendingWithoutReply = false,
                               bool protectContent = false,
                               std::int32_t messageThreadId = 0);

        Message::Ptr SendContact(boost::variant<std::int64_t, std::string> chatId,
                                 const std::string& phoneNumber,
                                 const std::string& firstName,
                                 const std::string& lastName = "",
                                 const std::string& vcard = "",
                                 bool disableNotification = false,
                                 std::int32_t replyToMessageId = 0,
                                 GenericReply::Ptr replyMarkup = nullptr,
                                 bool allowSendingWithoutReply = false,
                                 bool protectContent = false,
                                 std::int32_t messageThreadId = 0);

        Message::Ptr SendPoll(boost::variant<std::int64_t, std::string> chatId,
                              const std::string& question,
                              const std::vector<std::string>& options,
                              bool disableNotification = false,
                              std::int32_t replyToMessageId = 0,
                              GenericReply::Ptr replyMarkup = nullptr,
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

        Message::Ptr SendDice(boost::variant<std::int64_t, std::string> chatId,
                              bool disableNotification = false,
                              std::int32_t replyToMessageId = 0,
                              GenericReply::Ptr replyMarkup = nullptr,
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

        bool BanChatMember(boost::variant<std::int64_t, std::string> chatId,
                           std::int64_t userId,
                           std::int32_t untilDate = 0,
                           bool revokeMessages = true);

        bool UnbanChatMember(boost::variant<std::int64_t, std::string> chatId,
                             std::int64_t userId,
                             bool onlyIfBanned = false);

        bool RestrictChatMember(boost::variant<std::int64_t, std::string> chatId,
                                std::int64_t userId,
                                ChatPermissions::Ptr permissions,
                                std::int64_t untilDate = 0,
                                bool useIndependentChatPermissions = false);

        bool PromoteChatMember(boost::variant<std::int64_t, std::string> chatId,
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

        bool SetChatAdministratorCustomTitle(boost::variant<std::int64_t, std::string> chatId,
                                             std::int64_t userId,
                                             const std::string& customTitle);

        bool BanChatSenderChat(boost::variant<std::int64_t, std::string> chatId,
                               std::int64_t senderChatId);

        bool UnbanChatSenderChat(boost::variant<std::int64_t, std::string> chatId,
                                 std::int64_t senderChatId);

        bool SetChatPermissions(boost::variant<std::int64_t, std::string> chatId,
                                ChatPermissions::Ptr permissions,
                                bool useIndependentChatPermissions = false);

        std::string ExportChatInviteLink(boost::variant<std::int64_t, std::string> chatId);

        ChatInviteLink::Ptr CreateChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                                                 std::int32_t expireDate = 0,
                                                 std::int32_t memberLimit = 0,
                                                 const std::string& name = "",
                                                 bool createsJoinRequest = false);

        ChatInviteLink::Ptr EditChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                                               const std::string& inviteLink,
                                               std::int32_t expireDate = 0,
                                               std::int32_t memberLimit = 0,
                                               const std::string& name = "",
                                               bool createsJoinRequest = false);

        ChatInviteLink::Ptr RevokeChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                                                 const std::string& inviteLink);

        bool ApproveChatJoinRequest(boost::variant<std::int64_t, std::string> chatId,
                                    std::int64_t userId);

        bool DeclineChatJoinRequest(boost::variant<std::int64_t, std::string> chatId,
                                    std::int64_t userId);

        bool SetChatPhoto(boost::variant<std::int64_t, std::string> chatId,
                          InputFile::Ptr photo);

        bool DeleteChatPhoto(boost::variant<std::int64_t, std::string> chatId);

        bool SetChatTitle(boost::variant<std::int64_t, std::string> chatId,
                          const std::string& title);

        bool SetChatDescription(boost::variant<std::int64_t, std::string> chatId,
                                const std::string& description = "");

        bool PinChatMessage(boost::variant<std::int64_t, std::string> chatId,
                            std::int32_t messageId,
                            bool disableNotification = false);

        bool UnpinChatMessage(boost::variant<std::int64_t, std::string> chatId,
                              std::int32_t messageId = 0);

        bool UnpinAllChatMessages(boost::variant<std::int64_t, std::string> chatId);

        bool LeaveChat(boost::variant<std::int64_t, std::string> chatId);

        Chat::Ptr GetChat(boost::variant<std::int64_t, std::string> chatId);

        std::vector<ChatMember::Ptr> GetChatAdministrators(boost::variant<std::int64_t, std::string> chatId);

        std::int32_t GetChatMemberCount(boost::variant<std::int64_t, std::string> chatId);

        ChatMember::Ptr GetChatMember(boost::variant<std::int64_t, std::string> chatId,
                                      std::int64_t userId);

        bool SetChatStickerSet(boost::variant<std::int64_t, std::string> chatId,
                               const std::string& stickerSetName);

        bool DeleteChatStickerSet(boost::variant<std::int64_t, std::string> chatId);

        std::vector<Sticker::Ptr> GetForumTopicIconStickers();

        ForumTopic::Ptr CreateForumTopic(boost::variant<std::int64_t, std::string> chatId,
                                         const std::string& name,
                                         std::int32_t iconColor = 0,
                                         const std::string& iconCustomEmojiId = "");

        bool EditForumTopic(boost::variant<std::int64_t, std::string> chatId,
                            std::int32_t messageThreadId,
                            const std::string& name = "",
                            boost::variant<std::int8_t, std::string> iconCustomEmojiId = 0);

        bool CloseForumTopic(boost::variant<std::int64_t, std::string> chatId,
                             std::int32_t messageThreadId);

        bool ReopenForumTopic(boost::variant<std::int64_t, std::string> chatId,
                              std::int32_t messageThreadId);

        bool DeleteForumTopic(boost::variant<std::int64_t, std::string> chatId,
                              std::int32_t messageThreadId);

        bool UnpinAllForumTopicMessages(boost::variant<std::int64_t, std::string> chatId,
                                        std::int32_t messageThreadId);

        bool EditGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId,
                                   std::string name);

        bool CloseGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId);

        bool ReopenGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId);

        bool HideGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId);

        bool UnhideGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId);

        bool AnswerCallbackQuery(const std::string& callbackQueryId,
                                 const std::string& text = "",
                                 bool showAlert = false,
                                 const std::string& url = "",
                                 std::int32_t cacheTime = 0);

        bool SetMyCommands(const std::vector<BotCommand::Ptr>& commands,
                           BotCommandScope::Ptr scope = nullptr,
                           const std::string& languageCode = "");

        bool DeleteMyCommands(BotCommandScope::Ptr scope = nullptr,
                              const std::string& languageCode = "");

        std::vector<BotCommand::Ptr> GetMyCommands(BotCommandScope::Ptr scope = nullptr,
                                                   const std::string& languageCode = "");

        bool SetChatMenuButton(std::int64_t chatId = 0,
                               MenuButton::Ptr menuButton = nullptr);

        MenuButton::Ptr GetChatMenuButton(std::int64_t chatId = 0);

        bool SetMyDefaultAdministratorRights(ChatAdministratorRights::Ptr rights = nullptr,
                                             bool forChannels = false);

        ChatAdministratorRights::Ptr GetMyDefaultAdministratorRights(bool forChannels = false);

        Message::Ptr EditMessageText(const std::string& text,
                                     boost::variant<std::int64_t, std::string> chatId = 0,
                                     std::int32_t messageId = 0,
                                     const std::string& inlineMessageId = "",
                                     const std::string& parseMode = "",
                                     bool disableWebPagePreview = false,
                                     GenericReply::Ptr replyMarkup = nullptr,
                                     const std::vector<MessageEntity::Ptr>& entities = std::vector<MessageEntity::Ptr>());

        Message::Ptr EditMessageCaption(boost::variant<std::int64_t, std::string> chatId = 0,
                                        std::int32_t messageId = 0,
                                        const std::string& caption = "",
                                        const std::string& inlineMessageId = "",
                                        GenericReply::Ptr replyMarkup = nullptr,
                                        const std::string& parseMode = "",
                                        const std::vector<MessageEntity::Ptr>& captionEntities = std::vector<MessageEntity::Ptr>());

        Message::Ptr EditMessageMedia(InputMedia::Ptr media,
                                      boost::variant<std::int64_t, std::string> chatId = 0,
                                      std::int32_t messageId = 0,
                                      const std::string& inlineMessageId = "",
                                      GenericReply::Ptr replyMarkup = nullptr);

        Message::Ptr EditMessageReplyMarkup(boost::variant<std::int64_t, std::string> chatId = 0,
                                            std::int32_t messageId = 0,
                                            const std::string& inlineMessageId = "",
                                            GenericReply::Ptr replyMarkup = nullptr);

        Poll::Ptr StopPoll(boost::variant<std::int64_t, std::string> chatId,
                           std::int64_t messageId,
                           InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>());

        bool DeleteMessage(boost::variant<std::int64_t, std::string> chatId,
                           std::int32_t messageId);

        Message::Ptr SendSticker(boost::variant<std::int64_t, std::string> chatId,
                                 boost::variant<InputFile::Ptr, std::string> sticker,
                                 std::int32_t replyToMessageId = 0,
                                 GenericReply::Ptr replyMarkup = nullptr,
                                 bool disableNotification = false,
                                 bool allowSendingWithoutReply = false,
                                 bool protectContent = false,
                                 std::int32_t messageThreadId = 0);

        StickerSet::Ptr GetStickerSet(const std::string& name);

        std::vector<Sticker::Ptr> GetCustomEmojiStickers(const std::vector<std::string>& customEmojiIds);

        File::Ptr UploadStickerFile(std::int64_t userId,
                                    InputFile::Ptr pngSticker);

        bool CreateNewStickerSet(std::int64_t userId,
                                 const std::string& name,
                                 const std::string& title,
                                 const std::string& emojis,
                                 MaskPosition::Ptr maskPosition = nullptr,
                                 boost::variant<InputFile::Ptr, std::string> pngSticker = "",
                                 InputFile::Ptr tgsSticker = nullptr,
                                 InputFile::Ptr webmSticker = nullptr,
                                 const std::string& stickerType = "");

        bool AddStickerToSet(std::int64_t userId,
                             const std::string& name,
                             const std::string& emojis,
                             MaskPosition::Ptr maskPosition = nullptr,
                             boost::variant<InputFile::Ptr, std::string> pngSticker = "",
                             InputFile::Ptr tgsSticker = nullptr,
                             InputFile::Ptr webmSticker = nullptr);

        bool SetStickerPositionInSet(const std::string& sticker,
                                     std::int32_t position);

        bool DeleteStickerFromSet(const std::string& sticker);

        bool SetStickerSetThumb(const std::string& name,
                                std::int64_t userId,
                                boost::variant<InputFile::Ptr, std::string> thumb = "");

        bool AnswerInlineQuery(const std::string& inlineQueryId,
                               const std::vector<InlineQueryResult::Ptr>& results,
                               std::int32_t cacheTime = 300,
                               bool isPersonal = false,
                               const std::string& nextOffset = "",
                               const std::string& switchPmText = "",
                               const std::string& switchPmParameter = "");

        SentWebAppMessage::Ptr AnswerWebAppQuery(const std::string& webAppQueryId,
                                                 InlineQueryResult::Ptr result);

        Message::Ptr SendInvoice(boost::variant<std::int64_t, std::string> chatId,
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
                                 GenericReply::Ptr replyMarkup = nullptr,
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
                              InlineKeyboardMarkup::Ptr replyMarkup = std::make_shared<InlineKeyboardMarkup>(),
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

        std::string DownloadFile(const std::string& filePath,
                                 const std::vector<HttpReqArg>& args = std::vector<HttpReqArg>());

        bool BlockedByUser(std::int64_t chatId);
    };
}

#endif