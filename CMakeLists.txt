cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(TrainingCounter VERSION 1.0.0 LANGUAGES C CXX)

set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)

set(MAIN_MODULE TrainingCounter)

add_executable(${MAIN_MODULE})
target_sources(${MAIN_MODULE} PRIVATE
	src/main.cpp 
    src/AppCore.h src/AppCore.cpp
    src/OutputManager.h src/OutputManager.cpp
    src/Save.h src/Save.cpp
    src/LexerParser.h src/LexerParser.cpp
)
install(TARGETS ${MAIN_MODULE} 
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        CONFIGURATIONS Release 
        PERMISSIONS OWNER_EXECUTE)
