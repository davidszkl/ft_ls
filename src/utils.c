# include "ft_printf.h"
# include "ft_ls.h"

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

int ft_free_tab(char** tab, int rval) {
    while(*tab)
        free(*tab++);
    free(tab);
    return rval;
}

int ft_free_output_long(output_long_s* output_long, int rval) {
    free(output_long->perms);
    free(output_long->datetime);
    free(output_long->fname);
    free(output_long);
    return rval;
}

int ft_free_output_long_tab(output_long_s** output_long, int rval) {
    size_t count = output_long[0]->count ? output_long[0]->count : 1;
    for (size_t i = 0; i < count; i++) {
        ft_free_output_long(output_long[i], 0);
    }
    free(output_long);
    return rval;
}
char* ft_substr(const char* str, size_t begin, size_t end) {
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

int max(int a, int b) {
    return a > b ? a : b;
}

int numberlen(int nbr) {
    int rval = 1;
    while (nbr >= 10) {
        rval++;
        nbr /= 10;
    }
    return rval;
}