cmake_minimum_required(VERSION 2.8)

project(${PROJECT_NAME})

set(PROJECT_DIR	"../..")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_DIR}/bin/release)

include_directories(
    "${PROJECT_DIR}/../../common/include"
    "${PROJECT_DIR}/../../common/src"
    "${PROJECT_DIR}/../cots/lame-3.100/include")

link_directories(
	"/usr/lib"
	"/usr/local/lib")

add_definitions(-Wall -fmessage-length=0 -DDISABLE_LOG_SERVER)

file(GLOB_RECURSE SOURCES "${PROJECT_DIR}/../../common/src/*.cpp")  

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
           ${PROJECT_NAME} 
           mp3lame pthread)

