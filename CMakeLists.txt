cmake_minimum_required(VERSION 3.15)
project(Logger)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

find_package(Threads REQUIRED)

file(GLOB_RECURSE LOGGER_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/critical_error.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp"
)

file(GLOB_RECURSE LOGGER_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/critical_error.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Logger.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tools.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/exports.hpp"
)

set (CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(Logger SHARED ${LOGGER_SOURCES})
target_compile_definitions(Logger PRIVATE COMMON_EXPORTS)

add_executable(LoggerTest main.cpp)
target_link_libraries(LoggerTest Logger ${CMAKE_THREAD_LIBS_INIT})
