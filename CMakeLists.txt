cmake_minimum_required(VERSION 3.18)
project(netconfig
    VERSION 0.1
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(netconfig $<$<PLATFORM_ID:Windows>:netconfig_win.cc> $<$<PLATFORM_ID:Linux,Darwin>:netconfig_unix.cc>)
