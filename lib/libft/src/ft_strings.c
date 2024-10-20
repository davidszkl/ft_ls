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

size_t ft_strlen(const char* str)
{
    const char* begin = str;
    while (*++str) {}
    return (size_t)(str - begin);
}

size_t ft_numberlen(int nbr)
{
    size_t rval = 1;
    while (nbr >= 10) {
        rval++;
        nbr /= 10;
    }
    return rval;
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

int ft_strcmp(const char* str1, const char* str2)
{
    if (!str1 || !str2)
        return 1;
    while (*str1 && *str2) {
        if (*str1 != *str2)
            return *str1 - *str2;
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

int ft_strcmp_dot(const char* str1, const char* str2)
{
    // strcmp but dot is prioritised
    if (!str1 || !str2)
        return 1;
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            if (*str1 == '.') return 0;
            if (*str2 == '.') return 1;
            return  *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}
