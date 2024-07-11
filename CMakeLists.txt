cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(TrainingCounter VERSION 1.1.0 LANGUAGES C CXX)

set(MAIN_MODULE TrainingCounter)

add_executable(${MAIN_MODULE} src/main.cpp)

add_library(OutputManager src/OutputManager.cpp src/OutputManager.h)
add_library(Save src/Save.cpp src/Save.h)
add_library(Parser src/LexerParser.cpp src/LexerParser.h)

add_library(Core src/AppCore.cpp src/AppCore.h)
target_link_libraries(Core PRIVATE OutputManager Save Parser)

target_link_libraries(${MAIN_MODULE} PRIVATE Core)

set_target_properties(${MAIN_MODULE} PROPERTIES CXX_STANDARD 17)

install(TARGETS ${MAIN_MODULE} 
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        CONFIGURATIONS Release 
        PERMISSIONS OWNER_EXECUTE)
