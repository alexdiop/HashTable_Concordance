cmake_minimum_required(VERSION 3.15)
project(HASH_TABLE_CONCORDANCE)

set(CMAKE_CXX_STANDARD 14)

add_executable(HASH_TABLE_CONCORDANCE Entry.cpp Entry.h Dictionary.cpp Dictionary.h StartingConcordance.cpp)