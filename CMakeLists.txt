cmake_minimum_required(VERSION 3.22)

project(TelebotCpp)
set(ENABLE_TESTS FALSE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive -Wl,-allow-multiple-definition")

set(OPENSSL_USE_STATIC_LIBS TRUE)
set(OPENSSL_MSVC_STATIC_RT TRUE)
set(OPENSSL_ROOT_DIR "../OpenSSL")
find_package(OpenSSL REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ROOT "../boost_1_78_0")
set(BOOST_INCLUDEDIR "../boost_1_78_0")
set(BOOST_LIBRARYDIR "../boost_1_78_0/stage/lib")
find_package(Boost REQUIRED COMPONENTS system filesystem)

include_directories(include libs src ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

set(Headers include/Telebot.h include/Telebot/Api.h include/Telebot/HttpContext.h include/Telebot/HttpsClient.h
        include/Telebot/IEventHandler.h include/Telebot/Event.h include/Telebot/MethodHandler.h
        include/Telebot/StaticMethodHandler.h include/Telebot/CancellationTokenSource.h
        include/Telebot/CancellationToken.h include/Telebot/JsonMacros.h)

set(Source src/Telebot.cpp src/Api.cpp src/HttpContext.cpp src/HttpsClient.cpp
        src/CancellationTokenSource.cpp src/CancellationToken.cpp)

set(Types src/Types/BotCommandScope.cpp src/Types/ChatMember.cpp src/Types/InlineQueryResult.cpp
        src/Types/InputFile.cpp src/Types/InputMedia.cpp src/Types/InputMessageContent.cpp
        src/Types/MenuButton.cpp src/Types/PassportElementError.cpp)

set(PugiXML libs/PugiXml/pugiconfig.hpp libs/pugixml.hpp libs/PugiXml/pugixml.cpp)

set(Niohman_Json libs/Json/json_fwd.hpp libs/json.hpp)

add_library(TelebotCpp SHARED ${Headers} ${Source} ${Types} ${PugiXML} ${Niohman_Json})
target_link_libraries(TelebotCpp -static ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES})

add_subdirectory(../CInfoLog CInfoLog)
add_subdirectory(../LINQcpp LINQ)

set(MyBotHeaders)
set(MyBotSource MyBot/main.cpp)

add_executable(MyBot ${MyBotHeaders} ${MyBotSource})
target_link_libraries(MyBot TelebotCpp CInfoLog)

if (ENABLE_TESTS)
    add_subdirectory(../GoogleTest gtest)

    include_directories(tests)

    set(TESTS tests/main.cpp)

    add_executable(TelebotCpp_TEST ${TESTS})
    target_link_libraries(TelebotCpp_TEST TelebotCpp gtest pthread)
endif()

add_custom_command(
        TARGET TelebotCpp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/LogConfig.xml
        ${CMAKE_CURRENT_BINARY_DIR}/CInfoLog/LogConfig.xml)