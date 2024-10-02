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

    while (tmp >= 10) {
        size++;
        tmp /= 10;
    }

    char* res = malloc((size + 1) * sizeof(char));
    if (!res)
        return NULL;

    int i = size - 1;
    while (nbr >= 10) {
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

void *ft_memcpy(void *dst, const void *src, size_t n) {
    if (!dst || !src)
        return NULL;
    char* dest = (char*)dst;
    char* source = (char*)src;
    while (n--) {
        *dest++ = *source++;
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

char* ft_strtrim_one(const char* str, char c) {
    const char* left = str;
    const char* right = str;
    char* rval;
    int addone = 0;

    while (*str && *str == c)
        str++;
    if (str != left)
        left = str - 1;
    while (*str)
        str++;
    str--;
    while(*str && *str == c)
        str--;
    right = str + 1;
    // if (*right != c)
    //     addone = 1;

    rval = malloc(sizeof(char) * (right - left + addone + 1));
    if (!rval)
        return NULL;
    char* it = rval;
    while (left != right)
        *it++ = *left++;
    // if (addone)
    //     *it++ = c;
    *it = '\0';

    return rval;
}

const char* ft_find_str(const char* str, const char* to_find) {
    if (!str)
        return NULL;
    char* find_ptr;
    char* rval;
    while (*str) {
        if (*str == *to_find) {
            find_ptr = (char*)to_find;
            rval = (char*)str;
            while (*str && *find_ptr && *str == *find_ptr) {
                str++;
                find_ptr++;
            }
            if (!*str && *find_ptr)
                return NULL;
            if (!*find_ptr)
                return rval;
            str = rval;
        }
        str++;
    }
    return NULL;
}