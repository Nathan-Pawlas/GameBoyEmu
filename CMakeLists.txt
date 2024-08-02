cmake_minimum_required(VERSION 3.26) # FetchContent is available in 3.11+
project(GBEmu)

#Compiler Flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(SDL2 QUIET) # QUIET or REQUIRED
if (NOT SDL2_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    Set(FETCHCONTENT_QUIET FALSE)
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.26.3
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(SDL2)
endif()

include_directories("includes/")
# Project
add_executable(${PROJECT_NAME} src/main.cpp "src/gb.cpp" "includes/gb.h")
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} SDL2::SDL2main SDL2::SDL2-static)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

