cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(MAIN TrainingCounter)
set(CMAKE_BUILD_TYPE Release)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(${WIN32})
    add_compile_options("/utf-8")
endif()

add_subdirectory(external/CLIlib)
add_subdirectory(external/fmt)

project(
    ${MAIN}
    VERSION 1.7.3
    DESCRIPTION "A small utility for counting remaining workouts."
    HOMEPAGE_URL https://github.com/RomanBel94/TrainingCounter.git
    LANGUAGES CXX
)

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
)
target_link_libraries(TrainingCounterLib
    PRIVATE
    fmt::fmt
    CLIlib
)

add_executable(${MAIN})
target_sources(${MAIN}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
target_link_libraries(${MAIN}
    PRIVATE
    TrainingCounterLib
)

install(
    TARGETS ${MAIN}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    CONFIGURATIONS Release 
)

