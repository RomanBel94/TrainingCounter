cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# external libraries
add_subdirectory(external/CLIlib)

project(
    TrainingCounter
    VERSION 2.1.1
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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Version/Version.h.in 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Version/Version.h 
    NEWLINE_STYLE UNIX
)
message(STATUS "File \"Version.h\" configured with version: ${CMAKE_PROJECT_VERSION}")

add_library(TrainingCounterLib)
target_sources(TrainingCounterLib
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Counter/Counter.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Version/Version.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TrainingCounter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TrainingCounter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Logger/Logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Logger/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Counter/Save/Save.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TaskManager/Task/iTask.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TaskManager/TaskManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TaskManager/TaskManager.cpp
)
target_include_directories(
    TrainingCounterLib PUBLIC
    ${CMAKE_SOURCE_DIR}/external/CLIlib/include/
    ${CMAKE_SOURCE_DIR}/external/fmt/include/
)
target_link_libraries(TrainingCounterLib
    PRIVATE
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

add_custom_target(
    static_check
    COMMAND cppcheck --enable=all --std=c++${CMAKE_CXX_STANDARD} -I ${CMAKE_SOURCE_DIR}/external/CLIlib/include ${CMAKE_CURRENT_SOURCE_DIR}/src  >> ${CMAKE_CURRENT_BINARY_DIR}/check_result.txt
)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(
        doc
        COMMAND cd ${CMAKE_SOURCE_DIR} && doxygen 
    )
    message(STATUS "Added target \"doc\"")
else()
    message(WARNING "Doxygen is not found, target \"doc\" is not available")
endif()
