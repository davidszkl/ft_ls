# pragma once
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

# define FLAG_LEFT_PAD 1


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
int ft_strlen(const char* str);
int ft_isdigit(const char c);
size_t abs_value(long int nbr);
char* ft_memcpy(char* dst, char* src, size_t size);

int	ft_printf(const char *str, ...);
int	ft_read(const char *str, va_list list);
int	ft_put(char c, va_list list);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	putnbr(long int n);
int	putuint(unsigned long int n);
int	puthex(unsigned long int n, char *str);
int	putpointer(unsigned long int n, char *str);
long int get_padding(const char* str);
size_t compute_padding(size_t size, size_t padding);
size_t measure_int(long long int nbr);
size_t measure_unsigned(unsigned long long int nbr);
size_t measure_hex(unsigned long long int nbr);
size_t get_token_length(const char* str);
size_t write_formated(char* buffer, va_list list, char token, int padding);
char* format_string(const char* str, va_list list, char* buffer, size_t buffer_size);
char* resize_buffer(char* buffer, size_t* buffer_size, size_t required_size);
