project(vendor LANGUAGES C)

file(GLOB_RECURSE srcs include/*.h* src/*.c*)

add_library(${PROJECT_NAME} STATIC ${srcs})

target_include_directories(${PROJECT_NAME} PUBLIC include)