#include "Telebot/Api.h"

std::vector<Telebot::Update::Ptr> Telebot::Api::GetUpdates(int offset,
                                                           int limit,
                                                           int timeout,
                                                           const std::vector<std::string>& allowedUpdates)
{

}

bool Telebot::Api::SetWebhook(const std::string &url,
                              InputFile::Ptr certificate,
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

WebhookInfo::Ptr Telebot::Api::GetWebhookInfo()
{

}

Telebot::User::Ptr Telebot::Api::GetMe()
{

}

bool Telebot::Api::LogOut()
{

}

bool Telebot::Api::Close()
{

}

Telebot::Message::Ptr Telebot::Api::SendMessage(boost::variant<std::int64_t, std::string> chatId,
                                                 const std::string& text,
                                                 bool disableWebPagePreview,
                                                 std::int32_t replyToMessageId,
                                                 Telebot::GenericReply::Ptr replyMarkup,
                                                 const std::string& parseMode,
                                                 bool disableNotification,
                                                 const std::vector<MessageEntity::Ptr>& entities,
                                                 bool allowSendingWithoutReply,
                                                 bool protectContent,
                                                 std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::ForwardMessage(boost::variant<std::int64_t, std::string> chatId,
                                                   boost::variant<std::int64_t, std::string> fromChatId,
                                                   std::int32_t messageId,
                                                   bool disableNotification,
                                                   bool protectContent,
                                                   std::int32_t messageThreadId)
{

}

Telebot::MessageId::Ptr Telebot::Api::CopyMessage(boost::variant<std::int64_t, std::string> chatId,
                                                  boost::variant<std::int64_t, std::string> fromChatId,
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

Telebot::Message::Ptr Telebot::Api::SendPhoto(boost::variant<std::int64_t, std::string> chatId,
                                              boost::variant<InputFile::Ptr, std::string> photo,
                                              const std::string& caption,
                                              std::int32_t replyToMessageId,
                                              Telebot::GenericReply::Ptr replyMarkup,
                                              const std::string& parseMode,
                                              bool disableNotification,
                                              const std::vector<MessageEntity::Ptr>& captionEntities,
                                              bool allowSendingWithoutReply,
                                              bool protectContent,
                                              std::int32_t messageThreadId,
                                              bool hasSpoiler)
{

}

Telebot::Message::Ptr Telebot::Api::SendAudio(boost::variant<std::int64_t, std::string> chatId,
                                              boost::variant<InputFile::Ptr, std::string> audio,
                                              const std::string& caption,
                                              std::int32_t duration,
                                              const std::string& performer,
                                              const std::string& title,
                                              boost::variant<InputFile::Ptr, std::string> thumb,
                                              std::int32_t replyToMessageId,
                                              Telebot::GenericReply::Ptr replyMarkup,
                                              const std::string& parseMode,
                                              bool disableNotification,
                                              const std::vector<MessageEntity::Ptr>& captionEntities,
                                              bool allowSendingWithoutReply,
                                              bool protectContent,
                                              std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendDocument(boost::variant<std::int64_t, std::string> chatId,
                                                 boost::variant<InputFile::Ptr, std::string> document,
                                                 boost::variant<InputFile::Ptr, std::string> thumb,
                                                 const std::string& caption,
                                                 std::int32_t replyToMessageId,
                                                 Telebot::GenericReply::Ptr replyMarkup,
                                                 const std::string& parseMode,
                                                 bool disableNotification,
                                                 const std::vector<MessageEntity::Ptr>& captionEntities,
                                                 bool disableContentTypeDetection,
                                                 bool allowSendingWithoutReply,
                                                 bool protectContent,
                                                 std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendVideo(boost::variant<std::int64_t, std::string> chatId,
                                              boost::variant<InputFile::Ptr, std::string> video,
                                              bool supportsStreaming,
                                              std::int32_t duration,
                                              std::int32_t width,
                                              std::int32_t height,
                                              boost::variant<InputFile::Ptr, std::string> thumb,
                                              const std::string &caption,
                                              std::int32_t replyToMessageId,
                                              Telebot::GenericReply::Ptr replyMarkup,
                                              const std::string &parseMode,
                                              bool disableNotification,
                                              const std::vector<MessageEntity::Ptr>& captionEntities,
                                              bool allowSendingWithoutReply,
                                              bool protectContent,
                                              std::int32_t messageThreadId,
                                              bool hasSpoiler)
{

}

Telebot::Message::Ptr Telebot::Api::SendAnimation(boost::variant<std::int64_t, std::string> chatId,
                                                  boost::variant<InputFile::Ptr, std::string> animation,
                                                  std::int32_t duration,
                                                  std::int32_t width,
                                                  std::int32_t height,
                                                  boost::variant<InputFile::Ptr, std::string> thumb,
                                                  const std::string& caption,
                                                  std::int32_t replyToMessageId,
                                                  Telebot::GenericReply::Ptr replyMarkup,
                                                  const std::string &parseMode,
                                                  bool disableNotification,
                                                  const std::vector<MessageEntity::Ptr>& captionEntities,
                                                  bool allowSendingWithoutReply,
                                                  bool protectContent,
                                                  std::int32_t messageThreadId,
                                                  bool hasSpoiler)
{

}

Telebot::Message::Ptr Telebot::Api::SendVoice(boost::variant<std::int64_t, std::string> chatId,
                                              boost::variant<InputFile::Ptr, std::string> voice,
                                              const std::string &caption,
                                              std::int32_t duration,
                                              std::int32_t replyToMessageId,
                                              Telebot::GenericReply::Ptr replyMarkup,
                                              const std::string& parseMode,
                                              bool disableNotification,
                                              const std::vector<MessageEntity::Ptr>& captionEntities,
                                              bool allowSendingWithoutReply,
                                              bool protectContent,
                                              std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendVideoNote(boost::variant<std::int64_t, std::string> chatId,
                                                  boost::variant<InputFile::Ptr, std::string> videoNote,
                                                  std::int64_t replyToMessageId,
                                                  bool disableNotification,
                                                  std::int32_t duration,
                                                  std::int32_t length,
                                                  boost::variant<InputFile::Ptr, std::string> thumb,
                                                  Telebot::GenericReply::Ptr replyMarkup,
                                                  bool allowSendingWithoutReply,
                                                  bool protectContent,
                                                  std::int32_t messageThreadId)
{

}

std::vector<Message::Ptr> Telebot::Api::SendMediaGroup(boost::variant<std::int64_t, std::string> chatId,
                                                       const std::vector<InputMedia::Ptr>& media,
                                                       bool disableNotification,
                                                       std::int32_t replyToMessageId,
                                                       bool allowSendingWithoutReply,
                                                       bool protectContent,
                                                       std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendLocation(boost::variant<std::int64_t, std::string> chatId,
                                                 float latitude,
                                                 float longitude,
                                                 std::int32_t livePeriod,
                                                 std::int32_t replyToMessageId,
                                                 Telebot::GenericReply::Ptr replyMarkup,
                                                 bool disableNotification,
                                                 float horizontalAccuracy,
                                                 std::int32_t heading,
                                                 std::int32_t proximityAlertRadius,
                                                 bool allowSendingWithoutReply,
                                                 bool protectContent,
                                                 std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::EditMessageLiveLocation(float latitude,
                                                            float longitude,
                                                            boost::variant<std::int64_t, std::string> chatId,
                                                            std::int32_t messageId,
                                                            const std::string& inlineMessageId,
                                                            Telebot::InlineKeyboardMarkup::Ptr replyMarkup,
                                                            float horizontalAccuracy,
                                                            std::int32_t heading,
                                                            std::int32_t proximityAlertRadius)
{

}

Telebot::Message::Ptr Telebot::Api::StopMessageLiveLocation(boost::variant<std::int64_t, std::string> chatId,
                                                            std::int32_t messageId,
                                                            const std::string& inlineMessageId,
                                                            Telebot::InlineKeyboardMarkup::Ptr replyMarkup)
{

}

Telebot::Message::Ptr Telebot::Api::SendVenue(boost::variant<std::int64_t, std::string> chatId,
                                              float latitude,
                                              float longitude,
                                              const std::string& title,
                                              const std::string& address,
                                              const std::string& foursquareId,
                                              const std::string& foursquareType,
                                              bool disableNotification,
                                              std::int32_t replyToMessageId,
                                              Telebot::GenericReply::Ptr replyMarkup,
                                              const std::string& googlePlaceId,
                                              const std::string& googlePlaceType,
                                              bool allowSendingWithoutReply,
                                              bool protectContent,
                                              std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendContact(boost::variant<std::int64_t, std::string> chatId,
                                                const std::string& phoneNumber,
                                                const std::string& firstName,
                                                const std::string& lastName,
                                                const std::string& vcard,
                                                bool disableNotification,
                                                std::int32_t replyToMessageId,
                                                Telebot::GenericReply::Ptr replyMarkup,
                                                bool allowSendingWithoutReply,
                                                bool protectContent,
                                                std::int32_t messageThreadId)
{

}

Telebot::Message::Ptr Telebot::Api::SendPoll(boost::variant<std::int64_t, std::string> chatId,
                                             const std::string& question,
                                             const std::vector<std::string>& options,
                                             bool disableNotification,
                                             std::int32_t replyToMessageId,
                                             Telebot::GenericReply::Ptr replyMarkup,
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

Telebot::Message::Ptr Telebot::Api::SendDice(boost::variant<std::int64_t, std::string> chatId,
                                             bool disableNotification,
                                             std::int32_t replyToMessageId,
                                             Telebot::GenericReply::Ptr replyMarkup,
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

UserProfilePhotos::Ptr Telebot::Api::GetUserProfilePhotos(std::int64_t userId,
                                                          std::int32_t offset,
                                                          std::int32_t limit)
{

}

Telebot::File::Ptr Telebot::Api::GetFile(const std::string& fileId)
{

}

bool Telebot::Api::BanChatMember(boost::variant<std::int64_t, std::string> chatId,
                                 std::int64_t userId,
                                 std::int32_t untilDate,
                                 bool revokeMessages)
{

}

bool Telebot::Api::UnbanChatMember(boost::variant<std::int64_t, std::string> chatId,
                                   std::int64_t userId,
                                   bool onlyIfBanned)
{

}

bool Telebot::Api::RestrictChatMember(boost::variant<std::int64_t, std::string> chatId,
                                      std::int64_t userId,
                                      Telebot::ChatPermissions::Ptr permissions,
                                      std::int64_t untilDate,
                                      bool useIndependentChatPermissions)
{

}

bool Telebot::Api::PromoteChatMember(boost::variant<std::int64_t, std::string> chatId,
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

bool Telebot::Api::SetChatAdministratorCustomTitle(boost::variant<std::int64_t, std::string> chatId,
                                                   std::int64_t userId,
                                                   const std::string& customTitle)
{

}

bool Telebot::Api::BanChatSenderChat(boost::variant<std::int64_t, std::string> chatId,
                                     std::int64_t senderChatId)
{

}

bool Telebot::Api::UnbanChatSenderChat(boost::variant<std::int64_t, std::string> chatId,
                                       std::int64_t senderChatId)
{

}

bool Telebot::Api::SetChatPermissions(boost::variant<std::int64_t, std::string> chatId,
                                      Telebot::ChatPermissions::Ptr permissions,
                                      bool useIndependentChatPermissions)
{

}

std::string Telebot::Api::ExportChatInviteLink(boost::variant<std::int64_t, std::string> chatId)
{

}

Telebot::ChatInviteLink::Ptr Telebot::Api::CreateChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                                                                std::int32_t expireDate,
                                                                std::int32_t memberLimit,
                                                                const std::string& name,
                                                                bool createsJoinRequest)
{

}

Telebot::ChatInviteLink::Ptr Telebot::Api::EditChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                                                              const std::string& inviteLink,
                                                              std::int32_t expireDate,
                                                              std::int32_t memberLimit,
                                                              const std::string& name,
                                                              bool createsJoinRequest)
{

}

Telebot::ChatInviteLink::Ptr Telebot::Api::RevokeChatInviteLink(boost::variant<std::int64_t, std::string> chatId,
                                                                const std::string& inviteLink)
{

}

bool Telebot::Api::ApproveChatJoinRequest(boost::variant<std::int64_t, std::string> chatId,
                                          std::int64_t userId)
{

}

bool Telebot::Api::DeclineChatJoinRequest(boost::variant<std::int64_t, std::string> chatId,
                                          std::int64_t userId)
{

}

bool Telebot::Api::SetChatPhoto(boost::variant<std::int64_t, std::string> chatId,
                                InputFile::Ptr photo)
{

}

bool Telebot::Api::DeleteChatPhoto(boost::variant<std::int64_t, std::string> chatId)
{

}

bool Telebot::Api::SetChatTitle(boost::variant<std::int64_t, std::string> chatId,
                                const std::string& title)
{

}

bool Telebot::Api::SetChatDescription(boost::variant<std::int64_t,
                                      std::string> chatId,
                                      const std::string& description)
{

}

bool Telebot::Api::PinChatMessage(boost::variant<std::int64_t, std::string> chatId,
                                  std::int32_t messageId,
                                  bool disableNotification)
{

}

bool Telebot::Api::UnpinChatMessage(boost::variant<std::int64_t, std::string> chatId,
                                    std::int32_t messageId)
{

}

bool Telebot::Api::UnpinAllChatMessages(boost::variant<std::int64_t, std::string> chatId)
{

}

bool Telebot::Api::LeaveChat(boost::variant<std::int64_t, std::string> chatId)
{

}

Telebot::Chat::Ptr Telebot::Api::GetChat(boost::variant<std::int64_t, std::string> chatId)
{

}

std::vector<ChatMember::Ptr> Telebot::Api::GetChatAdministrators(boost::variant<std::int64_t, std::string> chatId)
{

}

std::int32_t Telebot::Api::GetChatMemberCount(boost::variant<std::int64_t, std::string> chatId)
{

}

Telebot::ChatMember::Ptr Telebot::Api::GetChatMember(boost::variant<std::int64_t, std::string> chatId,
                                                     std::int64_t userId)
{

}

bool
Telebot::Api::SetChatStickerSet(boost::variant<std::int64_t, std::string> chatId,
                                const std::string& stickerSetName)
{

}

bool Telebot::Api::DeleteChatStickerSet(boost::variant<std::int64_t, std::string> chatId)
{

}

std::vector<Sticker::Ptr> Telebot::Api::GetForumTopicIconStickers()
{

}

ForumTopic::Ptr Telebot::Api::CreateForumTopic(boost::variant<std::int64_t, std::string> chatId,
                                               const std::string& name,
                                               std::int32_t iconColor,
                                               const std::string& iconCustomEmojiId)
{

}

bool Telebot::Api::EditForumTopic(boost::variant<std::int64_t, std::string> chatId,
                                  std::int32_t messageThreadId,
                                  const std::string& name,
                                  boost::variant<std::int8_t, std::string> iconCustomEmojiId)
{

}

bool Telebot::Api::CloseForumTopic(boost::variant<std::int64_t, std::string> chatId, std::int32_t messageThreadId)
{

}

bool Telebot::Api::ReopenForumTopic(boost::variant<std::int64_t, std::string> chatId, std::int32_t messageThreadId)
{

}

bool Telebot::Api::DeleteForumTopic(boost::variant<std::int64_t, std::string> chatId, std::int32_t messageThreadId)
{

}

bool Telebot::Api::UnpinAllForumTopicMessages(boost::variant<std::int64_t, std::string> chatId,
                                              std::int32_t messageThreadId)
{

}

bool Telebot::Api::EditGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId, std::string name)
{

}

bool Telebot::Api::CloseGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId)
{

}

bool Telebot::Api::ReopenGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId)
{

}

bool Telebot::Api::HideGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId)
{

}

bool Telebot::Api::UnhideGeneralForumTopic(boost::variant<std::int64_t, std::string> chatId)
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
                                 BotCommandScope::Ptr scope,
                                 const std::string& languageCode)
{

}

bool Telebot::Api::DeleteMyCommands(BotCommandScope::Ptr scope,
                                    const std::string& languageCode)
{

}

std::vector<BotCommand::Ptr> Telebot::Api::GetMyCommands(BotCommandScope::Ptr scope,
                                                         const std::string& languageCode)
{

}

bool Telebot::Api::SetChatMenuButton(std::int64_t chatId, MenuButton::Ptr menuButton)
{

}

MenuButton::Ptr Telebot::Api::GetChatMenuButton(std::int64_t chatId)
{

}

bool Telebot::Api::SetMyDefaultAdministratorRights(ChatAdministratorRights::Ptr rights,
                                                   bool forChannels)
{

}

ChatAdministratorRights::Ptr Telebot::Api::GetMyDefaultAdministratorRights(bool forChannels)
{

}

Telebot::Message::Ptr Telebot::Api::EditMessageText(const std::string& text,
                                                    boost::variant<std::int64_t, std::string> chatId,
                                                    std::int32_t messageId,
                                                    const std::string& inlineMessageId,
                                                    const std::string& parseMode,
                                                    bool disableWebPagePreview,
                                                    Telebot::GenericReply::Ptr replyMarkup,
                                                    const std::vector<MessageEntity::Ptr>& entities)
{

}

Telebot::Message::Ptr Telebot::Api::EditMessageCaption(boost::variant<std::int64_t, std::string> chatId,
                                                       std::int32_t messageId,
                                                       const std::string& caption,
                                                       const std::string& inlineMessageId,
                                                       Telebot::GenericReply::Ptr replyMarkup,
                                                       const std::string& parseMode,
                                                       const std::vector<MessageEntity::Ptr>& captionEntities)
{

}

Telebot::Message::Ptr Telebot::Api::EditMessageMedia(InputMedia::Ptr media,
                                                     boost::variant<std::int64_t, std::string> chatId,
                                                     std::int32_t messageId,
                                                     const std::string& inlineMessageId,
                                                     Telebot::GenericReply::Ptr replyMarkup)
{

}

Telebot::Message::Ptr Telebot::Api::EditMessageReplyMarkup(boost::variant<std::int64_t, std::string> chatId,
                                                           std::int32_t messageId,
                                                           const std::string& inlineMessageId,
                                                           Telebot::GenericReply::Ptr replyMarkup)
{

}

Telebot::Poll::Ptr Telebot::Api::StopPoll(boost::variant<std::int64_t, std::string> chatId,
                                          std::int64_t messageId,
                                          Telebot::InlineKeyboardMarkup::Ptr replyMarkup)
{

}

bool Telebot::Api::DeleteMessage(boost::variant<std::int64_t, std::string> chatId,
                                 std::int32_t messageId)
{

}

Telebot::Message::Ptr Telebot::Api::SendSticker(boost::variant<std::int64_t, std::string> chatId,
                                                boost::variant<InputFile::Ptr, std::string> sticker,
                                                std::int32_t replyToMessageId,
                                                Telebot::GenericReply::Ptr replyMarkup,
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

Telebot::File::Ptr Telebot::Api::UploadStickerFile(std::int64_t userId, InputFile::Ptr pngSticker)
{

}

bool Telebot::Api::CreateNewStickerSet(std::int64_t userId,
                                       const std::string& name,
                                       const std::string& title,
                                       const std::string& emojis,
                                       MaskPosition::Ptr maskPosition,
                                       boost::variant<InputFile::Ptr, std::string> pngSticker,
                                       InputFile::Ptr tgsSticker,
                                       InputFile::Ptr webmSticker,
                                       const std::string& stickerType)
{

}

bool Telebot::Api::AddStickerToSet(std::int64_t userId,
                                   const std::string& name,
                                   const std::string& emojis,
                                   MaskPosition::Ptr maskPosition,
                                   boost::variant<InputFile::Ptr, std::string> pngSticker,
                                   InputFile::Ptr tgsSticker,
                                   InputFile::Ptr webmSticker)
{

}

bool Telebot::Api::SetStickerPositionInSet(const std::string& sticker,
                                           std::int32_t position)
{

}

bool Telebot::Api::DeleteStickerFromSet(const std::string& sticker)
{

}

bool Telebot::Api::SetStickerSetThumb(const std::string& name,
                                      std::int64_t userId,
                                      boost::variant<InputFile::Ptr, std::string> thumb)
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
                                                       InlineQueryResult::Ptr result)
{

}

Telebot::Message::Ptr Telebot::Api::SendInvoice(boost::variant<std::int64_t, std::string> chatId,
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
                                       GenericReply::Ptr replyMarkup,
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
                                            bool sendEmailToProvider
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
                                    InlineKeyboardMarkup::Ptr replyMarkup,
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

std::vector<GameHighScore::Ptr> Telebot::Api::GetGameHighScores(std::int64_t userId,
                                                                std::int64_t chatId,
                                                                std::int32_t messageId,
                                                                const std::string& inlineMessageId)
{

}

std::string Telebot::Api::DownloadFile(const std::string& filePath,
                                       const std::vector<HttpReqArg>& args)
{

}

bool Telebot::Api::BlockedByUser(std::int64_t chatId)
{

}