
cmake_minimum_required( VERSION 2.8 )
project (LazyCPP)

include_directories(	include
)

file( GLOB_RECURSE LAZYCPP_SOURCES src/*.cpp )

add_library(Lazycpp SHARED ${LAZYCPP_SOURCES} )

add_executable (Test apps/test.cpp)

target_link_libraries(Test Lazycpp)
