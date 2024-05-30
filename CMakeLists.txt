cmake_minimum_required( VERSION 2.8 )
project (LazyCPP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++0x -lstdc++ -msse2 -fPIC")

# ## TCMALLOC used to optimized memory allocation
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(TCMALLOC libtcmalloc_minimal)
# if(TCMALLOC_FOUND)
#     message("TCMALLOC FOUND")
#     include_directories(${TCMALLOC_INCLUDE_DIRS})
#     link_directories(${TCMALLOC_LIBRARY_DIRS})
#     list(APPEND MG_LIBRARIES ${TCMALLOC_LIBRARIES})
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free")
# endif(TCMALLOC_FOUND)

include_directories(	include
                        ${TCMALLOC_INCLUDE_DIRS}
)

link_directories(	${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}
                    ${TCMALLOC_LIBRARY_DIRS})

file( GLOB_RECURSE LazyCPP_SOURCES src/*.cpp )

add_library(LazyCPP SHARED ${LazyCPP_SOURCES} )

target_link_libraries(LazyCPP
                        ${TCMALLOC_LIBRARIES}
                        dl)

add_executable (Test apps/test.cpp)

target_link_libraries(Test LazyCPP)

### installation of the files
SET(INSTALL_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include/LazyCPP)
SET(INSTALL_LIB_DIRS ${CMAKE_INSTALL_PREFIX}/lib )

### Configure file
get_property(Include_Directories DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
SET(LazyCPP_INCLUDE_DIRS ${Include_Directories} ${INSTALL_INCLUDE_DIRS} CACHE INTERNAL "")
SET(LazyCPP_LIBRARIES LazyCPP CACHE INTERNAL "")
SET(LazyCPP_FLAGS ${CMAKE_CXX_FLAGS} CACHE INTERNAL "")
SET(LazyCPP_FOUND "TRUE" CACHE INTERNAL "")

configure_file(LazyCPPConfig.cmake.in "${PROJECT_BINARY_DIR}/LazyCPPConfig.cmake" @ONLY)

configure_file ("${PROJECT_SOURCE_DIR}/config_LazyCPP.h.in"
                "${PROJECT_SOURCE_DIR}/include/config_LazyCPP.h" )


# configure_file ("${PROJECT_SOURCE_DIR}/config_LazyCPP.h.in"
#                 "${PROJECT_SOURCE_DIR}/include/config_LazyCPP.h" )

install( FILES ${LazyCPP_HEADERS} DESTINATION ${INSTALL_INCLUDE_DIRS})
install( TARGETS LazyCPP LIBRARY DESTINATION ${INSTALL_LIB_DIRS}  COMPONENT main)

install(FILES "${PROJECT_BINARY_DIR}/LazyCPPConfig.cmake"
        DESTINATION "${INSTALL_LIB_DIRS}/LazyCPP" COMPONENT dev )
