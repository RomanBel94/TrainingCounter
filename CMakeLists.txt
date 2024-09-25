cmake_minimum_required(VERSION 3.8)

set(CXX_STANDARD 17)
set(MAIN TrainingCounter)
set(CMAKE_BUILD_TYPE Release)
message(STATUS "Build type is: ${CMAKE_BUILD_TYPE}")

project(
    ${MAIN}
    VERSION 1.5.8
    DESCRIPTION "A small utility for counting remaining workouts."
    HOMEPAGE_URL https://github.com/RomanBel94/TrainingCounter.git
    LANGUAGES CXX
)

add_library(OutputManager)
target_sources(OutputManager
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/OutputManager.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/OutputManager.h
)

add_library(Save)
target_sources(Save
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Save.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Save.h
)

add_library(Parser)
target_sources(Parser
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/LexerParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/LexerParser.h
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Version.hpp.in 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Version.hpp 
    NEWLINE_STYLE UNIX
)
message(STATUS "File \"Version.h\" configured with version: ${CMAKE_PROJECT_VERSION}")

add_library(Core)
target_sources(Core
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Counter.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Version.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AppCore.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AppCore.cpp
)
target_link_libraries(Core
    PRIVATE
    OutputManager
    Save
    Parser
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmt/libfmt.a
)
target_include_directories(Core
    PRIVATE
)

add_executable(${MAIN})
target_sources(${MAIN}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TrainingCounter.cpp
)
target_link_libraries(${MAIN}
    PRIVATE
    Core
)

install(
    TARGETS ${MAIN}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    CONFIGURATIONS Release 
)
