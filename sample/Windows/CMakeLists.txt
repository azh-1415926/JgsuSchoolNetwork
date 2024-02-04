cmake_minimum_required(VERSION 2.8.0)
project(login_win)

message(STATUS "The platform is ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "The project name is ${PROJECT_NAME}")

aux_source_directory(./src srcs)

include_directories(include)
add_executable(${PROJECT_NAME} ${srcs})
target_link_libraries(${PROJECT_NAME} ws2_32)