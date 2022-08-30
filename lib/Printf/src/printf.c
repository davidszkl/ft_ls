#include "printf.h"

#include "stdio.h"
int	ft_printf(const char *str, ...)
{
	va_list	list;
	int	   n;
    size_t ac = get_argc(str);
    size_t size;

	va_start(list, str);
    size = measure_output(str, ac, list);
    // printf("size = %ld\n", size);
	va_end(list);
    char *buffer = malloc(sizeof(char) * size + 1);
    if (!buffer)
        return -1;
    buffer[size] = 0;
    va_start(list, str);
	n = format_string(str, list, buffer);
	va_end(list);
    write(1, buffer, size + 1);
	return (size);
}

size_t get_argc(const char *str) {
    if (str == NULL)
        return 0;
    size_t n = 0;
    size_t ac = 0;
    while (str[n])
    {
        if (str[n++] == '%')
        {
            if (str[n] && !ft_isdigit(str[n]) && str[n] != '-')
                ac++;
            else
            {
                if (str[n] == '-')
                    n++;
                while (str[n] && ft_isdigit(str[n]))
                    n++;
                ac++;
            }
        }
    }
    return ac;
}

size_t measure_output(const char* str, size_t ac, va_list list) {
    size_t size = 0;
    size_t n = 0;
    size_t len = ft_strlen(str);
    char token;

    while (n < len) 
    {
        if (str[n] != '%') {
            size++;
            n++;
        }
        else
        {
            long int pad = get_padding(&str[n + 1]);
            pad = abs_value(pad);
            n += get_token_length(&str[n]);
            token = str[n];
            if (!token)
                return size + n;
            size_t arg_len = count_arg_len(list, token);
            size += arg_len > pad ? arg_len : pad;
            n++;
        }
    }

    return size;
}

size_t get_token_length(const char* str) {
    size_t n = 1;
    if (str[n] == '-')
        n++;
    while (str[n] && ft_isdigit(str[n]))
        n++;
    return n;
}

long int get_padding(const char* str) {
    if (!str[0])
        return 0;
    int rval = ft_atoi(str);
    return rval;
}

size_t compute_padding(size_t size, size_t padding) {
    if (size > padding)
        return size;
    else
        return padding;
}

size_t abs_value(long int nbr) {
    return nbr < 0 ? -nbr : nbr;
}

size_t count_arg_len(va_list list, char token) {
    if (token == 'c' && va_arg(list, int))
        return 1;
    if (token == '%')
        return 1;
    else if (token == 's')
        return ft_strlen(va_arg(list, char*));
    else if (token == 'd' || token == 'i')
		return measure_int(va_arg(list, int));
	else if (token == 'u')
        return measure_unsigned(va_arg(list, unsigned int));
	else if (token == 'x')
		return measure_hex(va_arg(list, unsigned int));
	else if (token == 'X')
		return measure_hex(va_arg(list, unsigned int));
	else if (token == 'p')
		return measure_hex(va_arg(list, unsigned long int)) + 2;
    return 0;
}

//"'%5c%c'\n"
int format_string(const char* str, va_list list, char* buffer) {
    size_t n = 0;
    size_t buff_n = 0;
    size_t len = ft_strlen(str);
    printf("len = %ld\n", len);
    long int padding = 0;
    char token;
    while (n < len) {
        // printf("n=%d\n",n);
        //printf("<");
        // for (int i = 0; i < 10; i++)
            // printf("%c", buffer[i] == 0 ? '_' : buffer[i]);
        // printf(">\n");
        printf("<%c>\n", str[n]);
        if (str[n] != '%') {
            printf("if\n");
            buffer[buff_n] = str[n];
            buff_n++;
            n++;
            // printf("str[%d] <%c>\nbuff[%d] <'%c%c'>\n", n, str[n], buff_n, buffer[buff_n - 1], buffer[buff_n]);
            continue;
        }
        printf("else\n");
        padding = get_padding(&str[n + 1]);
        // printf("string = <%s>\n", &str[n]);
        n += get_token_length(&str[n]);
        token = str[n];
        // printf("token = %c (%d)\n", str[n], n);
        buff_n += write_formated(&buffer[buff_n], list, token, padding);
        n++;
        // printf("str[%d] <%c>\nbuff[%d] <'%c%c'>\n", n, str[n], buff_n, buffer[buff_n - 1], buffer[buff_n]);
    }
}

size_t write_formated(char* buffer, va_list list, char token, int padding) {
    if (token == 'c') {
        int i = 1;
        size_t val = abs_value(padding);
        while(i < val)
            buffer[i++] = ' ';
        buffer[padding < 0 ? 0 : i] = va_arg(list, int);
        return i > 1 ? i : 2;
    }
    if (token == '%') {
        int i = -1;
        size_t val = abs_value(padding);
        for (; i < val; i++)
            buffer[i] = ' ';
        
        buffer[padding < 0 ? 0 : i] = '%';
        return i > 1 ? i : 2;
    }
    else if (token == 's')
        return ft_strlen(va_arg(list, char*));
    else if (token == 'd' || token == 'i')
		return measure_int(va_arg(list, int));
	else if (token == 'u')
        return measure_unsigned(va_arg(list, unsigned int));
	else if (token == 'x')
		return measure_hex(va_arg(list, unsigned int));
	else if (token == 'X')
		return measure_hex(va_arg(list, unsigned int));
	else if (token == 'p')
		return measure_hex(va_arg(list, unsigned long int)) + 2;
    return 0; 
}