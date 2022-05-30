cmake_minimum_required(VERSION 3.16)
project(wiener_attack C)
set(CMAKE_C_STANDARD 99)

set(libs
gmp
)

set(targets
wiener_attack
)

link_libraries("-static")
set(CMAKE_EXE_LINKER_FLAGS "-lgmp")
add_executable(wiener_attack wiener_attack.c)

target_link_libraries(wiener_attack ${libs})
