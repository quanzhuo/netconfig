cmake_minimum_required(VERSION 3.18)
project(netconfig
    VERSION 0.1
    LANGUAGES C CXX)
add_executable(netconfig $<$<PLATFORM_ID:Windows>:netconfig_win.cc> $<$<PLATFORM_ID:Linux,Darwin>:netconfig_unix.cc>)
