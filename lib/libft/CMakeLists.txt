set(LIBFT_PROJECT libft)
add_library(${LIBFT_PROJECT})
add_subdirectory(src)
target_include_directories(${LIBFT_PROJECT} PRIVATE inc)
