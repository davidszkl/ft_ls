#include <stdlib.h>
#include <stdio.h>
#include "printf.h"
#include "ft_ls.h"
int add(int a, int b);

int main(int ac, char **av) {
    (void)ac;    
    (void)av;
    // DIR* dir = opendir("/home/odoo/42_school/ft_ls");
    // struct dirent* entry;

    // while ((entry = readdir(dir)) != NULL) {
    // }
    // for (int a = 0; a < 10; a++) {
    // }
    ft_printf("%-20s%-20s%-20s\n", "file1", "file2", "file3");
    ft_printf("%-20s%-20s%-20s\n", "fileafr1", "file2", "file3");
    ft_printf("%-20s%-20s%-20s\n", "file1", "file2", "file3");
    ft_printf("%-20s%-20s%-20s\n", "file1", "fifawrle2", "file3");
    ft_printf("%-20s%-20s%-20s\n", "filsfae1", "file2", "file3");
    ft_printf("%-20s%-20s%-20s\n", "file1", "file2", "file3");
    ft_printf("%-20s%-20s%-20s\n", "filadfe1", "file2", "fildafse3");
    ft_printf("%-20s%-20s%-20s\n", "file1", "file2", "fildafe3");
    ft_printf("%-20s%-20s%-20s\n", "file1", "fifadle2", "file3");
    ft_printf("%-20s%-20s%-20s\n", "fiadfle1", "file2", "filafde3");
    // size_t rval2 = printf("%8d\n", 1234567);
    // printf("rval1 = %ld\n", rval1);
    // printf("rval2 = %ld\n", rval2);
    // printf("'%d'\n", add(1, 2));
    // ft_printf("'%5c%c'\n", 'a', 'b');
    //  '    a'
    return 1;
}