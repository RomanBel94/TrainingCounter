cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

add_subdirectory(external/CLIlib)
add_subdirectory(external/fmt)

project(
    TrainingCounter
    VERSION 2.0.2
    DESCRIPTION "A small utility for counting remaining workouts."
    HOMEPAGE_URL https://github.com/RomanBel94/TrainingCounter.git
    LANGUAGES CXX
)

# Utf-8 support for MSVC compiler
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_compile_options("/utf-8")
endif()

# Write project version Version.h file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Version.h.in 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Version.h 
    NEWLINE_STYLE UNIX
)
message(STATUS "File \"Version.h\" configured with version: ${CMAKE_PROJECT_VERSION}")

add_library(TrainingCounterLib)
target_sources(TrainingCounterLib
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Counter.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Version.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TrainingCounter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TrainingCounter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Save.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Save.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iTask.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TaskManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TaskManager.cpp
)
target_include_directories(
    TrainingCounterLib PUBLIC
    ${CMAKE_SOURCE_DIR}/external/CLIlib/include/
    ${CMAKE_SOURCE_DIR}/external/fmt/include/
)
target_link_libraries(TrainingCounterLib
    PRIVATE
    fmt::fmt
    CLIlib
)

add_executable(TrainingCounter)
target_sources(TrainingCounter
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
target_link_libraries(TrainingCounter
    PRIVATE
    TrainingCounterLib
)

install(
    TARGETS TrainingCounter
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    CONFIGURATIONS Release 
)

add_custom_target(
    run_test
    COMMAND valgrind ${CMAKE_CURRENT_BINARY_DIR}/TrainingCounter -h -ma1 -s`${CMAKE_CURRENT_BINARY_DIR}/TrainingCounter -T` -l5 -t --help --moo --meow
)

