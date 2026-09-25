cmake_minimum_required(VERSION 3.20)
project(IRCompiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(IRCompiler ${SOURCES}
        include/ast.h
        include/Ast.h
        include/Parser.h
        src/Parser.cpp)
target_include_directories(IRCompiler PRIVATE ${CMAKE_SOURCE_DIR}/include)