# include "ft_printf.h"

void ft_memset(void* mem, int c, size_t n) {
    unsigned char* p = (unsigned char*) mem; 
    while(n--)
        *p++ = (unsigned char)c;
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

int ft_strcmp_dot(const char* str1, const char* str2) {
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

int ft_free(void* ptr, int rval) {
    free(ptr);
    return rval;
}


char* ft_strjoin(const char* str1, const char* str2) {
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

char* ft_strjoin_path(const char* str1, const char* str2) {
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