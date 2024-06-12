cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(TrainingCounter VERSION 0.1 LANGUAGES C CXX)

set(MAIN_MODULE tc)

add_executable(${MAIN_MODULE})
target_sources(${MAIN_MODULE} PRIVATE src/main.cpp 
#    Core.h Core.cpp
#    Logger.h Logger.cpp
#    Save.h Save.cpp
#    Counter.h Counter.cpp
#    Lexer.h Lexer.cpp
#    Parser.h Parser.cpp
#    Menu.h Menu.cpp
)
target_include_directories(${MAIN_MODULE} PRIVATE src/)
# install(${MAIN_MODULE} <prefix>/bin)
