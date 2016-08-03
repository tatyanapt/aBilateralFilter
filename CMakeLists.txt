# This project is designed to be built outside the Insight source tree.
cmake_minimum_required(VERSION 2.8)
PROJECT(tbilateralfilter)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../bin)

#
# Project Headers
#
SET(P_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/aImage/aImage.h
)

#
# Project Sources
#
SET(P_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/aBilateralFilter.cxx 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/aImage/aImage.cxx
)

INCLUDE_DIRECTORIES(
                  ${CMAKE_CURRENT_SOURCE_DIR}
                  ${CMAKE_CURRENT_SOURCE_DIR}/../../include
                  ${CMAKE_CURRENT_SOURCE_DIR}/../../include/io
)
LINK_DIRECTORIES(
                  ${CMAKE_CURRENT_SOURCE_DIR}
                  ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
)

LINK_LIBRARIES( debug atkd optimized atk )


ADD_EXECUTABLE( ${PROJECT_NAME} Demo/main.cpp
                                ${P_SRCS}
)
