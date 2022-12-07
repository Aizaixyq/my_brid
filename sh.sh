project=("test")
sources=("src/*.cpp")
includedir=("src")
deps=("fmt" "sdl2" "SDL2_image")
pch_header="src/libheader.hpp"
compiler="clang++"
cflags=("-g" "-Wall")
mode="debug" 