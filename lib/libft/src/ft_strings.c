# include "libft.h"

char* ft_strtrim_one(const char* str, char c)
{
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

    rval = malloc(sizeof(char) * (right - left + addone + 1));
    if (!rval)
        return NULL;
    char* it = rval;
    while (left != right)
        *it++ = *left++;
    *it = '\0';

    return rval;
}

int ft_strlen(const char* str)
{
    int len = 0;
    while (*str++) {
        len++;
    }
    return len;
}

const char* ft_find_str(const char* str, const char* to_find)
{
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

const char* ft_strchr(const char c, const char* str)
{
    while (*str && *str != c)
        str++;
    return *str ? str : NULL;
}
