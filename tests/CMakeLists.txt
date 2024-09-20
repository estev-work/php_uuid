cmake_minimum_required(VERSION 3.10)
project(UUIDTests)

set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(test_uuid test_uuid.c ../lib/uuid.c)
