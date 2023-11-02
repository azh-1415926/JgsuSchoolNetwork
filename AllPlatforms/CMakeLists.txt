cmake_minimum_required(VERSION 2.8.0)
project(login)

aux_source_directory(./src srcs)

add_subdirectory(vendor)
include_directories(include)
add_executable(${PROJECT_NAME} ${srcs})

set(libs vendor)

if(CMAKE_HOST_WIN32)
    set(libs "${libs};ws2_32.lib")
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE ${libs})

message(STATUS "The platform is ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "The project name is ${PROJECT_NAME}")
message(STATUS "The source is ${srcs}")
message(STATUS "The lib is ${libs}")