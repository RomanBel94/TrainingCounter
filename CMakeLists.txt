cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(TrainingCounter VERSION 1.2.5.2 LANGUAGES C CXX)

set(MAIN_MODULE TrainingCounter)

add_library(OutputManager 
            ${CMAKE_CURRENT_SOURCE_DIR}/src/OutputManager.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/src/OutputManager.h)

set_target_properties(OutputManager PROPERTIES CXX_STANDARD 17)

add_library(Save 
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Save.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Save.h)

set_target_properties(Save PROPERTIES CXX_STANDARD 17)

add_library(Parser
            ${CMAKE_CURRENT_SOURCE_DIR}/src/LexerParser.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/LexerParser.h)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/Version.hpp.in 
               ${CMAKE_CURRENT_SOURCE_DIR}/src/Version.hpp 
               NEWLINE_STYLE UNIX)

add_library(Core 
            ${CMAKE_CURRENT_SOURCE_DIR}/src/AppCore.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/AppCore.h)

set_target_properties(Core PROPERTIES CXX_STANDARD 17)
target_link_libraries(Core PRIVATE OutputManager Save Parser)

add_executable(${MAIN_MODULE} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${MAIN_MODULE} PRIVATE Core)

set_target_properties(${MAIN_MODULE} PROPERTIES CXX_STANDARD 17)

install(TARGETS ${MAIN_MODULE} 
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        CONFIGURATIONS Release 
        PERMISSIONS OWNER_EXECUTE)
