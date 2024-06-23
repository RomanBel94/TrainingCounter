cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(TrainingCounter VERSION 0.1 LANGUAGES C CXX)

set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)

set(MAIN_MODULE tc)

add_executable(${MAIN_MODULE})
target_sources(${MAIN_MODULE} PRIVATE
	src/main.cpp 
    src/AppCore.h src/AppCore.cpp
    src/Logger.h src/Logger.cpp
    src/Save.h src/Save.cpp
    src/Counter.h src/Counter.cpp
    src/LexerParser.h src/LexerParser.cpp
    src/OutputManager.h src/OutputManager.cpp
)
install(TARGETS ${MAIN_MODULE} 
        DESTINATION usr/local/bin 
        CONFIGURATIONS Release 
        PERMISSIONS OWNER_EXECUTE)
