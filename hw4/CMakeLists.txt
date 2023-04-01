cmake_minimum_required(VERSION 3.24)
project(hw4 C)

set(CMAKE_C_STANDARD 11)

add_executable(hw4 main.c)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(hw4 ${CURL_LIBRARIES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONC REQUIRED json-c)
include_directories(${JSONC_INCLUDE_DIRS})
#link_directories(/usr/local/opt/json-c/lib/libjson-c.a)
target_link_libraries(hw4 /usr/local/opt/json-c/lib/libjson-c.a)
#target_link_libraries(hw4 ${JSONC_LIBRARIES})

#set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH})

#include_directories(/usr/local/opt/curl/include)
#include_directories(${JSONC_INCLUDE_DIRS})
#set(CURL_LIBRARIES /usr/local/opt/curl/lib/libcurl.a)

#include_directories("/usr/local/opt/json-c/include")
#set(JSONC_LIBRARIES "/usr/local/opt/json-c/lib/libjson-c.a")
#target_link_libraries(hw4 ${JSONC_LIBRARIES})

#CURL_LIBRARIES=/usr/local/opt/curl/lib/libcurl.a;DCURL_INCLUDE_DIR=/usr/local/opt/curl/include;DJSONC_INCLUDE_DIRS=/usr/local/opt/json-c/include
#CURL_LIBRARIES=/usr/local/opt/curl/lib/libcurl.a;DCURL_INCLUDE_DIR=/usr/local/opt/curl/include;DJSONC_INCLUDE_DIRS=/usr/local/opt/json-c/include;JSONC_LIBRARIES=/usr/local/opt/json-c/lib/libjson-c.a