cmake_minimum_required(VERSION 3.8)

set(MAIN TrainingCounter)

project(
    ${MAIN}
    VERSION 1.4.9.1
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
set_target_properties(OutputManager
    PROPERTIES
    CXX_STANDARD 17
)

add_library(Save)
target_sources(Save
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Save.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Save.h
)
set_target_properties(Save
    PROPERTIES
    CXX_STANDARD 17
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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AppCore.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AppCore.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Version.hpp
)
set_target_properties(Core
    PROPERTIES
    CXX_STANDARD 17
)
target_link_libraries(Core
    PRIVATE
    OutputManager
    Save
    Parser
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
set_target_properties(${MAIN}
    PROPERTIES
    CXX_STANDARD 17
)

install(
    TARGETS ${MAIN}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    CONFIGURATIONS Release 
)
