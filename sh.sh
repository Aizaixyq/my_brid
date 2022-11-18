project=("test")
sources=("src/*.cpp")
includedir=("src")
deps=("fmt" "sdl2")
pch_header="src/libheader.hpp"
compiler="clang++"
cflags=("-g" "-Wall")
mode="debug" 