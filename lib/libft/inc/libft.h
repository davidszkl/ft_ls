# pragma once
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <strings.h>
# include <limits.h>

// conversions
int	ft_atoi(const char *str);
char* ft_itoa(int nbr);

// math
size_t abs_value(long int nbr);

// memory
char* ft_strdup(const char* str, int size);
void* ft_memset(void* mem, int c, size_t n);
void *ft_memcpy(void *dst, const void *src, size_t n);

// strings
char* ft_strtrim_one(const char* str, char c);
int ft_strlen(const char* str);
const char* ft_find_str(const char* str, const char* to_find);
const char* ft_strchr(const char c, const char* str);

// types
int ft_isdigit(const char c);
