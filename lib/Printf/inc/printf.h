#pragma once
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int	ft_atoi(const char *str);
int ft_strlen(const char* str);
int ft_isdigit(const char c);

int	ft_printf(const char *str, ...);
int	ft_read(const char *str, va_list list);
int	ft_put(char c, va_list list);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr(long int n);
int	ft_putuint(unsigned long int n);
int	ft_puthex(unsigned long int n, char *str);
int	ft_putpointer(unsigned long int n, char *str);
long int get_padding(const char* str);
size_t get_argc(const char *str);
size_t compute_padding(size_t size, size_t padding);
size_t measure_output(const char* str, size_t ac, va_list list);
size_t measure_int(long long int nbr);
size_t measure_unsigned(unsigned long long int nbr);
size_t measure_hex(unsigned long long int nbr);
size_t get_token_length(const char* str);
size_t count_arg_len(va_list list, char token);
size_t write_formated(char* buffer, va_list list, char token, int padding);
size_t abs_value(long int nbr);
int format_string(const char* str, va_list list, char* buffer);
