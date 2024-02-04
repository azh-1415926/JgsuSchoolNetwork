project(login)

# file(GLOB_RECURSE srcs_c *.c)
# file(GLOB_RECURSE srcs_cxx *.cpp)
set(srcs_c client.c myinfo.c)
set(srcs_cxx client.cpp myinfo.c)

include_directories(include)
add_executable("${PROJECT_NAME}_C" ${srcs_c})
add_executable("${PROJECT_NAME}_CXX" ${srcs_cxx})

set(libs "vendor;AZH_Network_Program")

if(CMAKE_HOST_WIN32)
    set(libs "${libs};ws2_32.lib")
endif()
target_link_libraries("${PROJECT_NAME}_C" PRIVATE ${libs})
target_link_libraries("${PROJECT_NAME}_CXX" PRIVATE ${libs})

message(STATUS "Platform is ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "ProjectName is ${PROJECT_NAME}")