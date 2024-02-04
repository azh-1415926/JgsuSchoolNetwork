cmake_minimum_required(VERSION 2.8.0)
project(JgsuCampusNetwork)

add_subdirectory(vendor)
add_subdirectory(3rdparty/AZH_Network_Program)

include_directories(include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/3rdparty/AZH_Network_Program/include)

add_subdirectory(src)

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    message(STATUS "Build the Windows sample")
    add_subdirectory(sample/Windows)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "Build the Linux sample")
    add_subdirectory(sample/Linux)
endif()