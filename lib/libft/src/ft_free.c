# include "libft.h"

int ft_free(void* ptr, int rval)
{
    free(ptr);
    return rval;
}

int ft_free_tab(char** tab, int rval)
{
    while(*tab)
        free(*tab++);
    free(tab);
    return rval;
}