cmake_minimum_required(VERSION 3.16.3)

project(Ft_ls)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
add_compile_options(-Wall -Wextra -Wpedantic)
add_executable(${PROJECT_NAME})

add_subdirectory(src)
add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} PRIVATE inc lib/Printf/inc)
target_link_libraries(${PROJECT_NAME} Printf)
