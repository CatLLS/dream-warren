# dying over here trying to get this to work without visual studio because I wanted to save on memory.
# had to download the raylib source code and build it with cmake and make, then link it to my project. I also had to copy the assets folder to the build directory after compiling.
# I'll just use unreal and visual code next time.

cmake_minimum_required(VERSION 3.25)
project(DreamWarren LANGUAGES C CXX)

# Configurações do padrão C++ e C
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# 1. Caminho para a Raylib local que você extraiu
set(RAYLIB_DIR "C:/raylib") 

# 2. Criação do executável do seu jogo
add_executable(dream_warren
    src/main.cpp
    src/Dungeon.cpp
)

# 3. Vincula as pastas de cabeçalhos (.h) do seu projeto e da Raylib
target_include_directories(dream_warren PRIVATE src "${RAYLIB_DIR}/include")

# 4. Vincula a pasta de binários (.a / .lib) da Raylib local
target_link_directories(dream_warren PRIVATE "${RAYLIB_DIR}/lib")

# 5. Linka a biblioteca da Raylib ao seu executável
target_link_libraries(dream_warren PRIVATE raylib)

# 6. Como você usa MinGW (que entra no bloco else), ativa os avisos do compilador (-Wall -Wextra)
if(MSVC)
    target_compile_options(dream_warren PRIVATE /W4)
else()
    target_compile_options(dream_warren PRIVATE -Wall -Wextra)
endif()

# 7. No Windows com MinGW, precisamos linkar as bibliotecas do próprio Windows para gráficos e som
if(WIN32 AND NOT MSVC)
    target_link_libraries(dream_warren PRIVATE opengl32 gdi32 winmm shell32)
endif()

# 8. Copia a pasta de assets para junto do executável após compilar
add_custom_command(TARGET dream_warren POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:dream_warren>/assets
)
