# pragma once
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <strings.h>
# include <limits.h>

// conversions
int	ft_atoi(const char *str);
char* ft_itoa(int nbr);

// free
int ft_free(void* ptr, int rval);
int ft_free_tab(char** tab, int rval);

// math
size_t abs_value(long int nbr);
int max(int a, int b);

// memory
char* ft_strdup(const char* str, int size);
char* ft_strjoin(const char* str1, const char* str2);
char* ft_strjoin_path(const char* str1, const char* str2);
char* ft_strjoin_path(const char* str1, const char* str2);
char* ft_substr(const char* str, size_t begin, size_t end);
void* ft_memset(void* mem, int c, size_t n);
void* ft_memcpy(void *dst, const void *src, size_t n);
void* ft_malloc_zero(size_t size);

// strings
char* ft_strtrim_one(const char* str, char c);
int ft_strlen(const char* str);
int numberlen(int nbr);
const char* ft_find_str(const char* str, const char* to_find);
const char* ft_strchr(const char c, const char* str);
int ft_strcmp(const char* str1, const char* str2);
int ft_strcmp_dot(const char* str1, const char* str2);

// types
int ft_isdigit(const char c);
