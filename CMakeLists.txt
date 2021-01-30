cmake_minimum_required(VERSION 3.17)
project(QRcode C)

set(CMAKE_C_STANDARD 99)

set(SDL2_INCLUDE_DIR C:/Users/jeffr/CLionProjects/QRcode/SDL2/include)
set(SDL2_LIB_DIR C:/Users/jeffr/CLionProjects/QRcode/SDL2/lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(QRcode qrcodegen.c qrcodegen.h main.c)

target_include_directories(QRcode PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(QRcode ${SDL2_LIBRARIES})