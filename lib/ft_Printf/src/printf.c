# include "ft_printf.h"
// # include "utils.h"

# define BUFFER_SIZE 10
# define SUPPORTED_FLAGS "%dicsxXp"

char* free_buffer(buffer_s* buffer) {
    free(buffer->bytes);
    free(buffer);
    return NULL;
}

buffer_s* init_buffer() {
    buffer_s* buffer = (buffer_s*)malloc(sizeof(buffer_s));
    if (!buffer)
        return NULL;
    buffer->bytes = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buffer->bytes)
        return ((buffer_s*)free_buffer(buffer));
    bzero(buffer->bytes, BUFFER_SIZE + 1);
    buffer->capacity = BUFFER_SIZE;
    buffer->size = 0;
    return buffer;
}

int _get_flags(token_s* token, const char* str) {
    int rval = 0;
    while (*str) {
        if (*str == '0')
            token->padding = '0';
        else if (*str == '-')
            token->flags |= FLAG_JUSTIFY_LEFT;
        else if (ft_isdigit(*str) || ft_strchr(*str, SUPPORTED_FLAGS))
            return rval;
        else // unknown flag
            return -1;
        str++;
        rval++;
    }
    return -1;
}

int _get_width(token_s* token, const char* str) {
    if (ft_strchr(*str, SUPPORTED_FLAGS)) {
        token->width = 0;
        return 0;
    }
    int width = ft_atoi(str);
    int rval = 0;
    if (width < 0)
        return -1;
    token->width = width;
    str++; // first digit of the width
    rval++;
    while (width > 9) {
        rval++;
        str++;
        width /= 10;
    }
    return rval;
}

int _get_specifier(token_s* token, const char* str) {
    if (!*str)
        return -1;
    token->specifier = *str;
    return 1;
}

char* _get_token_string(const char* str) {
    const char* tmp = str;
    size_t len = 1; // skip the first '%'
    while (tmp[len] && !ft_strchr(tmp[len], SUPPORTED_FLAGS))
        len++;
    if (!tmp[len])
        return NULL;
    return ft_strdup(str, len + 1);
}

token_s* init_token(const char* token_str) {
    const char* tmp = token_str;
    int jump = 0;
    token_s* token = (token_s*)malloc(sizeof(token_s));
    if (!token)
        return NULL;
    bzero(token, sizeof(token_s));

    token->padding = ' '; // default value
    token_str++; // skip the '%'
    jump = _get_flags(token, token_str);
    if (jump < 0) {
        free(token);
        return NULL;
    }
    token_str += jump;
    jump = _get_width(token, token_str);
    if (jump < 0) {
        free(token);
        return NULL;
    }
    token_str += jump;
    jump = _get_specifier(token, token_str);
    if (jump < 0) {
        free(token);
        return NULL;
    }
    token_str += jump;
    token->size = (token_str - tmp) / sizeof(char);
    return token;
}

token_s* get_token(const char* str) {
    char* token_str = _get_token_string(str);
    if (!token_str)
        return NULL;
    token_s* token = init_token(token_str);
    free(token_str);
    return token;
}

const char* get_str_to_write(char specifier, va_list list) {
    char* str_to_write = NULL;
    if (specifier == 'c') {
        char c = va_arg(list, int);
        str_to_write = malloc(sizeof(char) * (1 + 1));
        if (!str_to_write)
            return NULL;
        str_to_write[0] = c;
        str_to_write[1] = '\0';
    }
    else if (specifier == '%') {
        str_to_write = malloc(sizeof(char) * (1 + 1));
        if (!str_to_write)
            return NULL;
        str_to_write[0] = '%';
        str_to_write[1] = '\0';
    }
    else if (specifier == 's') {
        char* str = va_arg(list, char*);
        if (!str)
            return ft_strdup("(null)", -1);
        str_to_write = ft_strdup(str, -1);
        if (!str_to_write)
            return NULL;
    }
    else if (specifier == 'd' || specifier == 'i') {
        int str = va_arg(list, int);
        str_to_write = ft_itoa(str);
        if (!str_to_write)
            return NULL;
    }

    return str_to_write;
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
    size_t new_capacity = buffer->capacity + required_size + BUFFER_SIZE + 1;
    char* new_buffer = malloc(sizeof(char) * new_capacity);
    if (!new_buffer)
        return NULL;
    bzero(new_buffer, new_capacity);

    ft_memcpy(new_buffer, buffer->bytes, buffer->size);
    free(buffer->bytes);
    buffer->bytes = new_buffer;
    buffer->capacity = new_capacity - 1;
    return new_buffer;
}

int write_to_buffer(buffer_s* buffer, const char* str, size_t len) {
    if (buffer->size + len > buffer->capacity)
        if (!resize_buffer(buffer, len)) return -1;
    ft_memcpy(buffer->bytes + buffer->size, str, len);
    buffer->size += len;
    return 0;
}

const char* get_sized_str(const char* str, const token_s* token){
    size_t strlen = ft_strlen(str);
    size_t width = strlen > token->width ? strlen : token->width;
    char* sized_str = malloc((width + 1) * sizeof(char));
    if (!sized_str)
        return NULL;
    bzero(sized_str, width + 1);

    char* rval = sized_str;
    int step = token->flags && FLAG_JUSTIFY_LEFT ? 1 : -1;
    const char* begin = token->flags && FLAG_JUSTIFY_LEFT ? str : str + strlen - 1;
    sized_str = token->flags && FLAG_JUSTIFY_LEFT ? sized_str : sized_str + width - 1;
    while (strlen) {
        *sized_str = *begin;
        begin += step;
        sized_str += step;
        strlen--;
        width--;
    }
    while (width) {
        *sized_str = token->padding;
        sized_str += step;
        width--;
    }

    return rval;
}

int write_token(buffer_s* buffer, token_s* token, va_list list) {
    const char *str_to_write = get_str_to_write(token->specifier, list);
    if (!str_to_write)
        return -1;
    const char *sized_str = get_sized_str(str_to_write, token);
    free((char *)str_to_write);
    if (!sized_str)
        return -1;
    size_t len = (size_t)ft_strlen(sized_str);
    
    if (write_to_buffer(buffer, sized_str, len) < 0) {
        free((char *)sized_str);
        return -1;
    }
    free((char *)sized_str);
    return len;
}

char* format_string(const char* str, va_list list, buffer_s* buffer) {
    // read through string, write characters to buffer until size, if size is reached, re-allocate. Stop at '%' character and handle.
    while (*str) {
        if (*str == '%') {
            token_s *token = get_token(str);
            if (!token)
                return NULL;
            if (write_token(buffer, token, list) < 0) {
                free(token);
                return NULL;
            }
            str += token->size;
            free(token);
        } else {
            if (write_to_buffer(buffer, str++, (size_t)1) < 0)
                return NULL;
        }
    }
    if (write_to_buffer(buffer, "\0", (size_t)1) < 0)
        return NULL;
    return buffer->bytes;
}

static buffer_s* ft_printf_helper(const char*str, va_list list) {
    buffer_s* buffer = init_buffer();
	buffer->bytes = format_string(str, list, buffer);
    if (!buffer->bytes) {
        free_buffer(buffer);
        return NULL;
    }
    return buffer;
}

int	ft_printf(const char *format, ...) {
    va_list	list;
    va_start(list, format);
	buffer_s* buffer = ft_printf_helper(format, list);
    va_end(list);
    write(STDOUT_FILENO, buffer->bytes, buffer->size);
    int len = buffer->size;
    free_buffer(buffer);
	return (len);
}

int ft_sprintf(char** str, const char* format, ...) {
    va_list	list;
    va_start(list, format);
    buffer_s* buffer = ft_printf_helper(format, list);
    va_end(list);
    *str = ft_strdup(buffer->bytes, -1);
    int len = buffer->size;
    free_buffer(buffer);
	return str ? len : -1;
}

int ft_dprintf(int fd, const char* format, ...) {
    va_list	list;
    va_start(list, format);
	buffer_s* buffer = ft_printf_helper(format, list);
    va_end(list);
    write(fd, buffer->bytes, buffer->size);
    int len = buffer->size;
    free_buffer(buffer);
	return (len);
}
