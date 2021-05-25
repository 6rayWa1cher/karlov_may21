cmake_minimum_required(VERSION 3.17)
project(karlov_may21)

set(CMAKE_CXX_STANDARD 14)

add_executable(karlov_may21 main.cpp
        number.cpp number.h
        utils.cpp utils.h
        array.cpp array.h
        multiplication.cpp multiplication.h tables.h)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

add_executable(tests test.cpp
        number.cpp number.h
        utils.cpp utils.h
        array.cpp array.h
        multiplication.cpp multiplication.h tables.h)

target_link_libraries(tests PRIVATE Catch2::Catch2)