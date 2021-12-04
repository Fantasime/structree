cmake_minimum_required(VERSION 3.10.2)

project(structree)

set(CMAKE_CXX_STANDARD_REQUIRED 11)

set(CMAKE_BUILD_TYPE "Debug")

if(MSVC)
  add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
  message(STATUS "structree: MSVC-Option: /utf-8")
endif(MSVC)

aux_source_directory(src STRUCTREE_SRC)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(structree ${STRUCTREE_SRC})