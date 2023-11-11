#include <stdlib.h>
#include <stdio.h>
#include "printf.h"
#include "ft_ls.h"
int add(int a, int b);

int main(int ac, char **av) {
    (void)ac;    
    (void)av;
    DIR* dir = opendir("/home/odoo/42_school/ft_ls");
    // struct dirent* entry;

    // while ((entry = readdir(dir)) != NULL) {
    // }
    size_t rval1 = ft_printf("abcdefghijklmnopqrstuvwxyz\n");
    size_t rval2 = printf("abcdefghijklmnopqrstuvwxyz\n");
    printf("rval1 = %ld\n", rval1);
    printf("rval2 = %ld\n", rval2);
    // printf("'%d'\n", add(1, 2));
    // ft_printf("'%5c%c'\n", 'a', 'b');
    //  '    a'
    return 1;
}