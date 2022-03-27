cmake_minimum_required(VERSION 3.1)

set(header person.h)
set(source person.cpp)
add_library(PersonLibrary ${source} ${header})

set(factory_header factories.h)
add_library(FactoryLibrary ${factory_header})