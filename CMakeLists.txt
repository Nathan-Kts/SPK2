cmake_minimum_required(VERSION 3.17)
project(TFE_KEM)

#set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.c)
add_executable(TFE_KEM ${SOURCE_FILES})

include_directories(src)
add_subdirectory(src)

target_link_libraries(TFE_KEM src)
