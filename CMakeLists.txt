cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(TrainingCounter VERSION 1.0.1 LANGUAGES C CXX)

set(MAIN_MODULE TrainingCounter)

add_executable(${MAIN_MODULE})

set_target_properties(${MAIN_MODULE} PROPERTIES CXX_STANDARD 17)

target_sources(${MAIN_MODULE} PRIVATE
	src/main.cpp 
    src/AppCore.cpp
    src/OutputManager.cpp
    src/Save.cpp
    src/LexerParser.cpp
)
install(TARGETS ${MAIN_MODULE} 
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        CONFIGURATIONS Release 
        PERMISSIONS OWNER_EXECUTE)
