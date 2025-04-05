cmake_minimum_required(VERSION 3.15)
project(Logger)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

find_package(Threads REQUIRED)

# Source files
set(LOGGER_SOURCES
    critical_error.cpp
    Logger.cpp
)

# Public headers (API)
set(PUBLIC_HEADERS
    Logger.hpp
)

# Private headers (not installed normally)
set(PRIVATE_HEADERS
    critical_error.hpp
    tools.hpp
    exports.hpp
)

# Remove warnings for unused variables in MSVC
# This is a common warning in MSVC and can be ignored in this case
if(MSVC)
    add_compile_options(/wd4505)
endif()

# Build the shared library
add_library(Logger SHARED ${LOGGER_SOURCES} ${PUBLIC_HEADERS})

# Define preprocessor macro
target_compile_definitions(Logger PRIVATE COMMON_EXPORTS)

# Set include directories for the library
target_include_directories(Logger PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Specify which headers are public/private for install(TARGETS)
set_target_properties(Logger PROPERTIES
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
    PRIVATE_HEADER "${PRIVATE_HEADERS}"
)

# Build a test executable
add_executable(LoggerTest main.cpp)
target_link_libraries(LoggerTest Logger ${CMAKE_THREAD_LIBS_INIT})

# Install library and headers
install(TARGETS Logger
    EXPORT LoggerTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    PRIVATE_HEADER DESTINATION include
)

# Optionally install the license and readme
install(FILES LICENSE README.md DESTINATION .)
# Export the targets for use in other projects
install(EXPORT LoggerTargets
    FILE LoggerTargets.cmake
    NAMESPACE Logger::
    DESTINATION lib/cmake/Logger
)

# Generate a config file for find_package()
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/LoggerConfigVersion.cmake"
    VERSION 1.0.0
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/LoggerConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/LoggerConfig.cmake"
    INSTALL_DESTINATION lib/cmake/Logger
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/LoggerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/LoggerConfigVersion.cmake"
    DESTINATION lib/cmake/Logger
)
