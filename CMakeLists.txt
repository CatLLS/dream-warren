cmake_minimum_required(VERSION 3.25)
project(DreamWarren LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download and build raylib automatically, so a fresh clone builds with no manual setup.
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
    SYSTEM   # treat raylib headers as external: no warnings from code that isn't yours
)
FetchContent_MakeAvailable(raylib)

add_executable(dream_warren
    src/main.cpp
    src/Dungeon.cpp
)
target_include_directories(dream_warren PRIVATE src)
target_link_libraries(dream_warren PRIVATE raylib)

if(MSVC)
    target_compile_options(dream_warren PRIVATE /W4)
else()
    target_compile_options(dream_warren PRIVATE -Wall -Wextra)
endif()

# Copy the assets folder next to the executable after every build,
# so LoadTexture("assets/...") works no matter where you run it from.
add_custom_command(TARGET dream_warren POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:dream_warren>/assets
)
