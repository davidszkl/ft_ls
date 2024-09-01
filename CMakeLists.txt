cmake_minimum_required(VERSION 3.16.3)

project(ft_ls)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra -Wpedantic)
add_executable(${PROJECT_NAME})

add_subdirectory(src)
add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} PRIVATE inc lib/ft_Printf/inc)
target_link_libraries(${PROJECT_NAME} ft_Printf)
