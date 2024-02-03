# include "ft_printf.h"

int	ft_atoi(const char *str)
{
	unsigned int nbr = 0;
	int sign = 1;

	while (*str && ((*str >= 9 && *str <= 13) || *str == ' ')) {
		str++;
    }
	if (*str && (*str == '-' || *str == '+')) {
        if (*str == '-')
		    sign = -1;
        str++;
    }
	while (*str && *str >= '0' && *str <= '9') {
		nbr = nbr * 10 + *str - '0';
		str++;
	}
    if (!*str) return -1;
	if (sign == 1 && nbr > INT_MAX) return (-1);
	if (sign == -1 && nbr > (unsigned int)INT_MAX + 1) return (0);

	return nbr * sign;
}

char* ft_itoa(int nbr) {
    int	tmp = nbr;
    size_t size = 1;

    while (tmp > 10) {
        size++;
        tmp /= 10;
    }

    char* res = malloc((size + 1) * sizeof(char));
    if (!res)
        return NULL;

    int i = size - 1;
    while (nbr > 10) {
        res[i--] = nbr % 10 + '0';
        nbr /= 10;
    }
    res[i] = nbr + '0';
    res[size] = '\0';

    return res;
}

int ft_strlen(const char* str) {
    int len = 0;
    while (*str++) {
        len++;
    }
    return len;
}

int ft_isdigit(const char c) {
    return c >= '0' && c <= '9';
}

size_t abs_value(long int nbr) {
    return nbr < 0 ? -nbr : nbr;
}

char* ft_memcpy(char* dst, const char* src, size_t size) {
    if (!dst || !src)
        return NULL;
    while (*src && size--) {
        *dst++ = *src++;
    }
    return dst;
}

char* ft_strdup(const char* str, int size){
    char* res = NULL;
    if (size < 0) {
        const char* tmp = str;
        size = 0;
        while (*tmp++)
            size++;
    }
    res = malloc((size + 1) * sizeof(char));
    if (!res)
        return NULL;
    char* rval = res;
    while (*str && size--) {
        *res++ = *str++;
    }
    *res = '\0';
    return rval;
}

const char* ft_strchr(const char c, const char* str) {
    while (*str && *str != c)
        str++;
    return *str ? str : NULL;
}
