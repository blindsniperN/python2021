cmake_minimum_required(VERSION 3.1)

set(header phrases.h)
set(source phrases.cpp)
add_library(PhrasesLibrary ${source} ${header})