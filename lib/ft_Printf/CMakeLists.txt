set(PRINTF_PROJECT ft_Printf)
add_library(${PRINTF_PROJECT})
add_subdirectory(src)
target_include_directories(${PRINTF_PROJECT} PRIVATE inc)
