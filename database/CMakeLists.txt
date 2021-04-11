cmake_minimum_required(VERSION 3.1)

set(header database.h)
set(source database.cpp)
add_library(DatabaseLibrary ${source} ${header})
