cmake_minimum_required(VERSION 2.8)
project(rapidjsonwrapper)

message("config types: ${CMAKE_CONFIGURATION_TYPES}")

set(CMAKE_BUILD_TYPE Release)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(include
                    lib/rapidjson/include
)

set(SOURCE_FILES
    src/main.cpp
    include/rapidjsonwrapper/rapidjsonwrapper.hpp
)

add_executable(rapidjsonwrapper ${SOURCE_FILES})
# add_subdirectory(test)
