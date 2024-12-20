# include "ft_printf.h"

# define BUFFER_SIZE 80
# define SUPPORTED_FLAGS "%dicsxXp"

static char* free_buffer(buffer_s* buffer) {
    free(buffer->bytes);
    free(buffer);
    return NULL;
}

static buffer_s* init_buffer() {
    buffer_s* buffer = (buffer_s*)malloc(sizeof(buffer_s));
    if (!buffer)
        return NULL;
    buffer->bytes = ft_malloc_zero(sizeof(char) * BUFFER_SIZE + 1);
    if (!buffer->bytes)
        return ((buffer_s*)free_buffer(buffer));
    buffer->capacity = BUFFER_SIZE;
    buffer->size = 0;
    return buffer;
}

static int _get_flags(token_s* token, const char* str) {
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

static int _get_width(token_s* token, const char* str) {
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

static int _get_specifier(token_s* token, const char* str) {
    if (!*str)
        return -1;
    token->specifier = *str;
    return 1;
}

static char* _get_token_string(const char* str) {
    const char* tmp = str;
    size_t len = 1; // skip the first '%'
    while (tmp[len] && !ft_strchr(tmp[len], SUPPORTED_FLAGS))
        len++;
    if (!tmp[len])
        return NULL;
    return ft_strdup(str, len + 1);
}

static int init_token(const char* token_str, token_s* token) {
    const char* tmp = token_str;
    int jump = 0;

    token->padding = ' '; // default value
    token_str++; // skip the '%'
    jump = _get_flags(token, token_str);
    if (jump < 0)
        return 1;

    token_str += jump;
    jump = _get_width(token, token_str);
    if (jump < 0)
        return 1;

    token_str += jump;
    jump = _get_specifier(token, token_str);
    if (jump < 0)
        return 1;

    token_str += jump;
    token->size = (token_str - tmp) / sizeof(char);
    return 0;
}

static int get_token(const char* str, token_s* token) {
    char* token_str = _get_token_string(str);
    if (!token_str)
        return 1;
    if (init_token(token_str, token))
        return 1;
    free(token_str);
    return 0;
}

char get_next_digit(int* nbr, int nbr_size, int backwards) {
    int rval = 0;
    if (*nbr < 10) {
        rval = *nbr + '0';
        *nbr = 0;
        return rval;
    }
    int pow = ft_pow(10, nbr_size - 1);
    rval = backwards ? *nbr % 10 : *nbr / pow;
    *nbr = backwards ? *nbr / 10 : *nbr - (rval * pow);
    return rval + '0';
}

static const char* get_sized_str_nbr(int nbr, const token_s* token){
    size_t strlen = ft_numberlen(nbr);
    size_t width = strlen > token->width ? strlen : token->width;
    char* sized_str = ft_malloc_zero((width + 1) * sizeof(char));
    if (!sized_str)
        return NULL;

    char* rval = sized_str;
    int step = token->flags && FLAG_JUSTIFY_LEFT ? -1 : 1;
    int backwards = step == -1;
    sized_str = token->flags && FLAG_JUSTIFY_LEFT ? sized_str + width - 1 : sized_str;
    while (strlen) {
        *sized_str = get_next_digit(&nbr, (int)strlen, backwards);
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

static const char* get_sized_str(const char* str, const char c, const token_s* token){
    size_t strlen = c ? 1 : ft_strlen(str);
    size_t width = strlen > token->width ? strlen : token->width;
    char* sized_str = ft_malloc_zero((width + 1) * sizeof(char));
    if (!sized_str)
        return NULL;

    char* rval = sized_str;
    int step = token->flags && FLAG_JUSTIFY_LEFT ? 1 : -1;
    const char* str_to_use = c ? &c : str;
    const char* begin = token->flags && FLAG_JUSTIFY_LEFT ? str_to_use : str_to_use + strlen - 1;
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

static const char* get_str_to_write(char specifier, va_list list, token_s* token) {
    const char* str_to_write = NULL;
    if (specifier == 'c') {
        char c = va_arg(list, int);
        str_to_write = get_sized_str(NULL, c, token);
        if (!str_to_write)
            return NULL;
    }
    else if (specifier == '%') {
        char c = '%';
        str_to_write = get_sized_str(NULL, c, token);
        if (!str_to_write)
            return NULL;
    }
    else if (specifier == 's') {
        char* str = va_arg(list, char*);
        if (!str)
            str = "(null)";
        str_to_write = get_sized_str(str, 0, token);
        if (!str_to_write)
            return NULL;
    }
    else if (specifier == 'd' || specifier == 'i') {
        int str = va_arg(list, int);
        //1,389,6,4096
        str_to_write = get_sized_str_nbr(str, token);
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

static char* resize_buffer(buffer_s* buffer, size_t required_size) {
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

static int write_to_buffer(buffer_s* buffer, const char* str, size_t len) {
    if (buffer->size + len > buffer->capacity)
        if (!resize_buffer(buffer, len)) return -1;
    ft_memcpy(buffer->bytes + buffer->size, str, len);
    buffer->size += len;
    return 0;
}

static int write_token(buffer_s* buffer, token_s* token, va_list list) {
    const char *str_to_write = get_str_to_write(token->specifier, list, token);
    if (!str_to_write)
        return -1;
    
    size_t len = (size_t)ft_strlen(str_to_write);
    if (write_to_buffer(buffer, str_to_write, len) < 0) {
        free((char *)str_to_write);
        return -1;
    }
    free((char *)str_to_write);
    return len;
}

static char* format_string(const char* str, va_list list, buffer_s* buffer) {
    // read through string, write characters to buffer until size, if size is reached, re-allocate. Stop at '%' character and handle.
    token_s token = {0};
    while (*str) {
        if (*str == '%') {
            if (get_token(str, &token))
                return NULL;
            if (write_token(buffer, &token, list) < 0)
                return NULL;
            str += token.size;
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
        free(buffer);
        return NULL;
    }
    return buffer;
}

int	ft_printf(const char *format, ...) {
    va_list	list;
    va_start(list, format);
	buffer_s* buffer = ft_printf_helper(format, list);
    va_end(list);
    if (!buffer || !buffer->bytes) {
        free(buffer);
        return 1;
    }
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
    if (!buffer || !buffer->bytes) {
        free(buffer);
        return 1;
    }
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
    if (!buffer || !buffer->bytes) {
        free(buffer);
        return 1;
    }
    write(fd, buffer->bytes, buffer->size);
    int len = buffer->size;
    free_buffer(buffer);
	return (len);
}
