cmake_minimum_required(VERSION 3.22)

project(TelebotCpp)
set(ENABLE_TESTS TRUE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive -Wl,-allow-multiple-definition")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive -Wl,-allow-multiple-definition")

set(OPENSSL_USE_STATIC_LIBS TRUE)
set(OPENSSL_MSVC_STATIC_RT TRUE)
set(OPENSSL_ROOT_DIR ../OpenSSL)
find_package(OpenSSL REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ROOT ../boost_1_78_0)
set(BOOST_INCLUDEDIR ../boost_1_78_0)
set(BOOST_LIBRARYDIR ../boost_1_78_0/stage/lib)
find_package(Boost REQUIRED COMPONENTS system filesystem)

find_package(PostgreSQL REQUIRED)

include_directories(include libs MyBot src ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ../CInfoLog/include
        ${PostgreSQL_INCLUDE_DIR} ../libpqxx-7.7.5/include)

set(CommonHeaders include/Common/HttpContext.h include/Common/HttpsClient.h include/Common/IEventHandler.h
        include/Common/Event.h include/Common/MethodHandler.h include/Common/StaticMethodHandler.h
        include/Common/CancellationTokenSource.h include/Common/CancellationToken.h)

set(CommonSource src/Common/HttpContext.cpp src/Common/HttpsClient.cpp src/Common/CancellationTokenSource.cpp
        src/Common/CancellationToken.cpp)

set(PugiXML libs/PugiXml/pugiconfig.hpp libs/pugixml.hpp libs/PugiXml/pugixml.cpp)

set(Niohman_Json libs/Json/json_fwd.hpp libs/json.hpp)

add_library(Common SHARED ${CommonHeaders} ${CommonSource} ${PugiXML} ${Niohman_Json})
target_link_libraries(Common ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES})

set(TelebotHeaders include/Telebot.h include/Telebot/TelebotApi.h include/Common/JsonMacros.h)

set(TelebotSource src/Telebot/Telebot.cpp src/Telebot/TelebotApi.cpp)

set(TelebotTypes src/Telebot/Types/BotCommandScope.cpp src/Telebot/Types/ChatMember.cpp
        src/Telebot/Types/InlineQueryResult.cpp src/Telebot/Types/InputFile.cpp src/Telebot/Types/InputMedia.cpp
        src/Telebot/Types/InputMessageContent.cpp src/Telebot/Types/MenuButton.cpp
        src/Telebot/Types/PassportElementError.cpp)

add_library(Telebot SHARED ${TelebotHeaders} ${TelebotSource} ${TelebotTypes})
target_link_libraries(Telebot Common)

set(OpenAIHeaders include/OpenAI.h include/OpenAI/OpenAIApi.h include/OpenAI/GptModel.h include/OpenAI/GptTurbo.h)

set(OpenAISource src/OpenAI/OpenAI.cpp src/OpenAI/OpenAIApi.cpp src/OpenAI/GptModel.cpp src/OpenAI/GptTurbo.cpp)

set(OpenAITypes include/OpenAI/Types/ChatCompletionsRequest.h include/OpenAI/Types/ChatCompletionsResponse.h
        include/OpenAI/Types/Usage.h include/OpenAI/Types/Message.h)

add_library(OpenAI SHARED ${OpenAIHeaders} ${OpenAISource} ${OpenAITypes})
target_link_libraries(OpenAI Common)

add_subdirectory(../CInfoLog CInfoLog)
add_subdirectory(../LINQcpp LINQ)
add_subdirectory(../libpqxx-7.7.5 pqxx)

set(MyBotHeaders MyBot/MyBot.h include/Db/DbPool.h include/Db/DbConnection.h MyBot/User.h)

set(MyBotSource MyBot/main.cpp MyBot/MyBot.cpp src/Db/DbPool.cpp src/Db/DbConnection.cpp)

add_executable(MyBot ${MyBotHeaders} ${MyBotSource})
target_link_libraries(MyBot Telebot OpenAI CInfoLog ${PostgreSQL_LIBRARIES} pqxx)

if (ENABLE_TESTS)
    add_subdirectory(../GoogleTest gtest)

    include_directories(tests)

    set(Common_TESTS tests/Common/main.cpp)

    add_executable(Common_TEST ${Common_TESTS})
    target_link_libraries(Common_TEST Common gtest pthread)

    set(Telebot_TESTS tests/Telebot/main.cpp)

    add_executable(Telebot_TEST ${Telebot_TESTS})
    target_link_libraries(Telebot_TEST Telebot gtest pthread)

    set(OpenAI_TESTS tests/OpenAI/main.cpp)

    add_executable(OpenAI_TEST ${OpenAI_TESTS})
    target_link_libraries(OpenAI_TEST OpenAI gtest pthread)
endif()

add_custom_command(
        TARGET MyBot POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/LogConfig.xml
        ${CMAKE_CURRENT_BINARY_DIR}/LogConfig.xml)