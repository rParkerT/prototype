project(prototype)
cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CC=gcc-10.2)
set(CXX=g++-10.2)

set(CMAKE_CXX_COMPILER_ID GNU)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(impl)

find_package(Doxygen OPTIONAL_COMPONENTS dot)
if (DOXYGEN_FOUND)
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md")
  doxygen_add_docs(doc
    ${CMAKE_SOURCE_DIR}
  )
endif(DOXYGEN_FOUND)

add_custom_target(ALL COMMAND make run
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/impl
)
