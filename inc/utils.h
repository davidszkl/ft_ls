# pragma once
# include "ft_ls.h"

void ft_memset(void* mem, char c, size_t n);
int ft_strcmp(const char* str1, const char* str2);
int ft_strcmp_dot(const char* str1, const char* str2);
int ft_free(void* ptr, int rval);
char* ft_strjoin(const char* str1, const char* str2);
char* ft_strjoin_path(const char* str1, const char* str2);
