# pragma once
# include <stdarg.h>
# include "libft.h"

# define FLAG_JUSTIFY_LEFT 1

typedef struct buffer_s {
    size_t size;
    size_t capacity;
    char* bytes;
} buffer_s;

typedef struct token_s {
    size_t size; // size of the token in the format
    size_t width;
    char flags;
    char padding;
    char specifier;
} token_s;

int	ft_printf(const char *format, ...);
int ft_sprintf(char** str, const char* format, ...);
int ft_dprintf(int fd, const char* format, ...);
