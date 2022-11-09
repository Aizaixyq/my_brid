add_rules("mode.debug", "mode.release")
add_requires("libsdl", "fmt")

target("pvz")
    set_kind("binary")
    set_languages("cxx20")
    set_pcxxheader("src/libheader.hpp")
    add_includedirs("src")
    add_files("src/*.cpp")
    add_packages("libsdl", "fmt")