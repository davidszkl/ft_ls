# pragma once
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>

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

int	ft_atoi(const char *str);
char* ft_itoa(int nbr);
int ft_strlen(const char* str);
int ft_isdigit(const char c);
size_t abs_value(long int nbr);
char* ft_memcpy(char* dst, const char* src, size_t size);
void ft_memset(char* mem, char c);
char* ft_strdup(const char* str, int size);
const char* ft_strchr(const char c, const char* str);

int	ft_read(const char *str, va_list list);
int	ft_put(char c, va_list list);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	putnbr(long int n);
int	putuint(unsigned long int n);
int	puthex(unsigned long int n, char *str);
int	putpointer(unsigned long int n, char *str);

int	ft_printf(const char *str, ...);
