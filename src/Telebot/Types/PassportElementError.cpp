#include "Telebot/Types/PassportElementErrorDataField.h"
#include "Telebot/Types/PassportElementErrorFrontSide.h"
#include "Telebot/Types/PassportElementErrorReverseSide.h"
#include "Telebot/Types/PassportElementErrorSelfie.h"
#include "Telebot/Types/PassportElementErrorFile.h"
#include "Telebot/Types/PassportElementErrorFiles.h"
#include "Telebot/Types/PassportElementErrorTranslationFile.h"
#include "Telebot/Types/PassportElementErrorTranslationFiles.h"
#include "Telebot/Types/PassportElementErrorUnspecified.h"

const std::string Telebot::PassportElementErrorDataField::SOURCE = "data";
const std::string Telebot::PassportElementErrorFrontSide::SOURCE = "front_side";
const std::string Telebot::PassportElementErrorReverseSide::SOURCE = "reverse_side";
const std::string Telebot::PassportElementErrorSelfie::SOURCE = "selfie";
const std::string Telebot::PassportElementErrorFile::SOURCE = "file";
const std::string Telebot::PassportElementErrorFiles::SOURCE = "files";
const std::string Telebot::PassportElementErrorTranslationFile::SOURCE = "translation_file";
const std::string Telebot::PassportElementErrorTranslationFiles::SOURCE = "translation_files";
const std::string Telebot::PassportElementErrorUnspecified::SOURCE = "unspecified";