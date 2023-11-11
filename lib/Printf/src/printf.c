# include "printf.h"

# define BUFFER_SIZE 10


int	ft_printf(const char *str, ...) {
	va_list	list;
    
    buffer_s* buffer = init_buffer();
    
    va_start(list, str);
	buffer->bytes = format_string(str, list, buffer, BUFFER_SIZE);
	va_end(list);

    ft_putstr(buffer->bytes);
    int len = buffer->size;
    free(buffer->bytes);
    free(buffer);
	return (len);
}

buffer_s* init_buffer() {
    buffer_s* buffer = (buffer_s*)malloc(sizeof(buffer_s));
    if (!buffer)
        return -1;
    buffer->bytes = malloc(sizeof(char) * BUFFER_SIZE);
    if (!buffer->bytes) {
        free(buffer);
        return NULL;
    }
    buffer->capacity = BUFFER_SIZE;
    buffer->size = 0;
    return buffer;
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

char* get_flags(token_s* token, char* str) {
    while (*str) {
        if (*str == '0')
            token->padding = '0';
        else if (*str == '-')
            token->flags |= FLAG_LEFT_PAD;
        else
            return str;
        str++;
    }
    return NULL;
}

char* get_width(token_s* token, char* str) {
    size_t width = (size_t)ft_atoi(str);
    if (width < 0)
        return NULL;
    token->width = width;
    return str;
}

char* get_specifier(token_s* token, char* str) {
    if (*str != '%' && *str != 'd' && *str != 'i' && *str != 'c' && *str != 's' && *str != 'x' && *str != 'X' && *str != 'p')
        return NULL;
    token->specifier = *str++;
    return str;
}

token_s* get_token(char* str) {
    char* tmp = str;
    if (*str != '%')
        return NULL;
    token_s* token = (token_s*)malloc(sizeof(token_s));
    if (!token)
        return NULL;
    str = get_flags(&token, str);
    str = get_width(&token, str);
    str = get_specifier(&token, str);
    token->size = (str - tmp) / sizeof(char);
    return token;
}

//"'%5c%c'\n"
char* format_string(const char* str, va_list list, buffer_s* buffer, size_t buffer_size) {
    // read through string, write characters to buffer until size, if size is reached, re-allocate. Stop at '%' character and handle.
    size_t curr_size = 0;
    while (*str) {
        if (*str == '%') {
            token_s *token = get_token(str);
            str += write_token(buffer, token, list);
        } else {
            write_to_buffer(buffer, str++, (size_t)1);
        }
    }
    buffer->bytes[buffer->size] = '\0';
    return buffer->bytes;
}

size_t write_token(buffer_s* buffer, token_s* token, va_list list) {
    char *str_to_write = get_str_to_write(token->specifier, list);
    size_t len = (size_t)ft_strlen(str_to_write);
    
    if (write_to_buffer(buffer, str_to_write, len) < 0)
        return NULL; 
    return len;
}

int write_to_buffer(buffer_s* buffer, const char* str, size_t len) {
    if (buffer->size + len > buffer->capacity)
        if (!resize_buffer(buffer, len))
            return -1;
    ft_memcpy(buffer->bytes + buffer->size, str, len);
    buffer->size += len;
    return 0;
}

char* get_str_to_write(char specifier, va_list list) {
    char* str_to_write = NULL;
    if (specifier == 'c') {
        char c = va_arg(list, char);
        str_to_write = malloc(sizeof(char));
        if (!str_to_write)
            return NULL;
        *str_to_write = c;
    }
    else if (specifier == '%') {
        str_to_write = malloc(sizeof(char));
        if (!str_to_write)
            return NULL;
        *str_to_write = '%';
    }
    else if (specifier == 's') {
        char* str = va_arg(list, char*);
        str_to_write = malloc(sizeof(char) * ft_strlen(str));
        if (!str_to_write)
            return NULL;
        *str_to_write = str;
    }
    return str_to_write;
    // else if (token == 'd' || token == 'i')
	// 	return measure_int(va_arg(list, int));
	// else if (token == 'u')
    //     return measure_unsigned(va_arg(list, unsigned int));
	// else if (token == 'x')
	// 	return measure_hex(va_arg(list, unsigned int));
	// else if (token == 'X')
	// 	return measure_hex(va_arg(list, unsigned int));
	// else if (token == 'p')
	// 	return measure_hex(va_arg(list, unsigned long int)) + 2;
}

char* resize_buffer(buffer_s* buffer, size_t required_size) {
    size_t new_size = buffer->capacity + required_size + BUFFER_SIZE;
    char* new_buffer = malloc(sizeof(char) * new_size);
    if (!new_buffer)
        return NULL;

    ft_memcpy(new_buffer, buffer->bytes, buffer->size);
    free(buffer->bytes);
    buffer->bytes = new_buffer;
    buffer->size = new_size;
    return new_buffer;
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