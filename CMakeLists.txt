cmake_minimum_required(VERSION 3.17)
project(QRcode C)

set(CMAKE_C_STANDARD 99)

add_executable(QRcode qrcodegen.c qrcodegen.h main.c reader.c)