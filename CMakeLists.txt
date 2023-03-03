cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(dbc_parser)

include_directories(
   src/
   include/
   test/
)

set(SRC_FILES
   src/Comment.cpp
   src/Entry.cpp
   src/main.cpp
   src/Message.cpp
   src/Parser.cpp
   src/Sig_ValType.cpp
   src/Signal.cpp
   src/Util.cpp
   src/Val_Table.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(
   ${PROJECT_NAME}
)

add_executable( test test/newsimpletest.cpp )
target_link_libraries(
   test
)