cmake_minimum_required(VERSION 3.20)

list( APPEND CMAKE_MODULE_PATH, "CMAKE_CURRENT_LIST_DIR/cmake")
include(cmake/scripts/BootstrapVcpkg.cmake)

project(SpaceTraders)

add_subdirectory(src)
