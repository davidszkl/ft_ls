# include "libft.h"

char* ft_strdup(const char* str, int size)
{
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

char* ft_strjoin(const char* str1, const char* str2)
{
    if (!str1 || !str2)
        return NULL;
    char* rval = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
    char* rval_initial = rval;
    if (!rval)
        return NULL;
    while (*str1)
        *rval++ = *str1++;
    while (*str2)
        *rval++ = *str2++;
    *rval = '\0';
    return rval_initial;
}

char* ft_strjoin_path(const char* str1, const char* str2)
{
    if (!str1 || !str2)
        return NULL;
    char* rval = malloc(ft_strlen(str1) + ft_strlen(str2) + 2);
    if (!rval)
        return NULL;
    char* rval_initial = rval;
    while (*str1)
        *rval++ = *str1++;
    *rval++ = '/';
    while (*str2)
        *rval++ = *str2++;
    *rval = '\0';
    return rval_initial;
}

char* ft_substr(const char* str, size_t begin, size_t end)
{
    if (end < begin)
        return NULL;
    char* rval = malloc(sizeof(char) * (end - begin + 1));
    if (!rval)
        return NULL;
    char* it = rval;
    while(begin < end)
        *it++ = str[begin++];
    *it = '\0';
    return rval;
}

void* ft_memset(void* mem, int c, size_t n)
{
    unsigned char* p = (unsigned char*) mem; 
    while(n--)
        *p++ = (unsigned char)c;
    return mem;
}

void* ft_memcpy(void *dst, const void *src, size_t n)
{
    if (!dst || !src)
        return NULL;
    char* dest = (char*)dst;
    char* source = (char*)src;
    while (n-- && *source) {
        *dest++ = *source++;
    }

    return dst;
}

void* ft_memcpy_any(void *dst, const void *src, size_t n)
{
    if (!dst || !src)
        return NULL;
    char* dest = (char*)dst;
    char* source = (char*)src;
    while (n--) {
        *dest++ = *source++;
    }

    return dst;
}

void* ft_malloc_zero(size_t size)
{
    void* rval = malloc(size);
    if (!rval)
        return NULL;
    ft_memset(rval, 0, size);
    return rval;
}
