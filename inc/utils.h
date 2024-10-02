# pragma once
# include "ft_ls.h"

void* ft_memset(void* mem, char c, size_t n);
int ft_strcmp(const char* str1, const char* str2);
int ft_strcmp_dot(const char* str1, const char* str2);
int ft_free(void* ptr, int rval);
int ft_free_tab(char** tab, int rval);
int ft_free_output_long(output_long_s* output_long, int rval);
int ft_free_output_long_tab(output_long_s** output_long, int rval);
char* ft_strjoin(const char* str1, const char* str2);
char* ft_strjoin_path(const char* str1, const char* str2);
char* ft_strtrim_one(const char* str, char c);
const char* ft_find_str(const char* str, const char* to_find);
char* ft_substr(const char* str, size_t begin, size_t end);
int max(int a, int b);
int numberlen(int nbr);
int is_dot_folder(char* name);
int is_symbolic_link(struct stat* stat);
int is_hidden_folder(char* name);
void* ft_malloc_zero(size_t size);
