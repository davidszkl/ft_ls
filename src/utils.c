# include "ft_printf.h"

void ft_memset(void* mem, int c, size_t n) {
    unsigned char* p = (unsigned char*) mem; 
    while(*p && n--)
        *p++ = c;
}

void *ft_memcpy(void *dest, const void *source, size_t n) {
    char* dst = (char*)dest;
    char* src = (char*)source;
    while (n--) {
        *dst++ = *src++;
    }

    return dest;
}

int ft_strcmp(const char* str1, const char* str2) {
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

int ft_free(void* ptr, int rval) {
    free(ptr);
    return rval;
}
