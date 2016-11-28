cmake_minimum_required(VERSION 3.0)
#project name
PROJECT(adts_parser)
#head file path
INCLUDE_DIRECTORIES(
include
)
#source directory
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
#set environment variable
SET(ADTS_PARSER
${DIR_SRCS}
)
#set extern libraries
#SET(LIBRARIES
#libm.so
#)
#add executable file
ADD_EXECUTABLE(adts_parser ${ADTS_PARSER})
#add link library
#TARGET_LINK_LIBRARIES(../bin/bin ${LIBRARIES})

