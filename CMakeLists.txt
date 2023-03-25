cmake_minimum_required(VERSION 3.22)

project(TelebotCpp)
set(ENABLE_TESTS TRUE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive -Wl,-allow-multiple-definition")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ROOT "../boost_1_78_0")
set(BOOST_INCLUDEDIR "../boost_1_78_0")
set(BOOST_LIBRARYDIR "../boost_1_78_0/stage/lib")
find_package(Boost REQUIRED COMPONENTS system)

set(OPENSSL_USE_STATIC_LIBS TRUE)
set(OPENSSL_MSVC_STATIC_RT TRUE)
set(OPENSSL_ROOT_DIR "../OpenSSL")
find_package(OpenSSL REQUIRED)

include_directories(include libs src ${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})
add_subdirectory(../LINQcpp LINQ)

set(Headers include/Telebot/Bot.h include/Telebot/Api.h include/Telebot/HttpContext.h
        include/Telebot/HttpServer.h include/Telebot/HttpClient.h include/Telebot/Configuration.h
        include/Telebot/HttpRequest.h  include/Telebot/HttpResponse.h)

set(Source src/Bot.cpp src/Api.cpp src/HttpContext.cpp src/HttpServer.cpp src/HttpResponse.cpp
        src/HttpClient.cpp src/Configuration.cpp src/HttpRequest.cpp)

set(Types src/Types/ChatMember.cpp)

set(PugiXML libs/pugiconfig.hpp libs/pugixml.hpp libs/pugixml.cpp)

add_library(TelebotCpp SHARED ${Headers} ${Source} ${Types} ${PugiXML})
target_link_libraries(TelebotCpp -static ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

add_subdirectory(../CInfoLog CInfoLog)

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

    add_custom_command(
            TARGET TelebotCpp POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/LogConfig.xml
            ${CMAKE_CURRENT_BINARY_DIR}/CInfoLog/LogConfig.xml)
endif()