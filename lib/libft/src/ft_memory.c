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


void* ft_memset(void* mem, int c, size_t n)
{
    unsigned char* p = (unsigned char*) mem; 
    while(n--)
        *p++ = (unsigned char)c;
    return mem;
}

void *ft_memcpy(void *dst, const void *src, size_t n)
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
