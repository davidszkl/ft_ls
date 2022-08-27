#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "ft_ls.h"

int main(int ac, char **av) {
    (void)ac;    
    (void)av;
    // DIR* dir = opendir("/home/odoo/42_school/ft_ls");
    // struct dirent* entry;

    // while ((entry = readdir(dir)) != NULL) {
    // }
    int a = printf(   "-%c-%s-%d-%5i-%-10x-%1X-%p-%%-\n", 'z', "bad", 1234, 1234, 1234, 1234, &a);
    int b = ft_printf("-%c-%s-%d-%5i-%-10x-%1X-%p-%%-\n", 'z', "bad", 1234, 1234, 1234, 1234, &a);
    printf("a = %d\nb = %d\n", a, b);
    // ft_printf("%s %s %s %s\n", "arg1", "arg2", "arg3", "arg4");
    return 1;
}

//-z-bad-1234-1234-4d2-4D2-0x7ffea46ffcb0-%-