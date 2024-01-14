#include <stdlib.h>
#include <stdio.h>
#include "printf.h"
#include "ft_ls.h"

int test_printf() {
    ft_printf("testing no specifier\n");
    ft_printf("1\n");
    ft_printf("123456789\n");
    ft_printf("1234567890\n");
    ft_printf("12345678901\n");

    ft_printf("testing 'c' specifier no buffer\n");
    
    ft_printf("%c%c\n", 'a', 'b');
    ft_printf("1%c%c\n", 'a', 'b');
    ft_printf("%c2%c\n", 'a', 'b');
    ft_printf("%c%c\n", 'a', 'b');
    ft_printf("%c2%c\n", 'a', 'b');
    ft_printf("1%c2%c\n", 'a', 'b');

    ft_printf("testing 'c' specifier buffer exact\n");
    ft_printf("1234567%c\n", 'a');
    ft_printf("12345%c%c\n", 'a', 'b');
    ft_printf("1234%cb%c\n", 'a', 'b');

    ft_printf("testing 'c' specifier 1 over\n");
    ft_printf("12345678%c\n", 'a');
    ft_printf("123456%c%c\n", 'a', 'b');
    ft_printf("12345%cb%c\n", 'a', 'b');

    ft_printf("testing 'c' specifier others\n");
    ft_printf("%c%c%c%c%c%c%c\n", 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a');

    ft_printf("testing 'c' specifier padding\n");
    ft_printf("%0c\n", 'a');
    ft_printf("%-c\n", 'a');
    ft_printf("%-0c\n", 'a');

    ft_printf("%5c\n", 'a');
    ft_printf("%9c\n", 'a');
    ft_printf("%10c\n", 'a');

    ft_printf("%-5c\n", 'a');
    ft_printf("%-9c\n", 'a');
    ft_printf("%-10c\n", 'a');

    ft_printf("%05c\n", 'a');
    ft_printf("%09c\n", 'a');
    ft_printf("%010c\n", 'a');

    ft_printf("%-05c\n", 'a');
    ft_printf("%-09c\n", 'a');
    ft_printf("%-010c\n", 'a');

    ft_printf("testing 'c' specifier mixed flags\n");
    ft_printf("%-0-00--00-10c\n", 'a');

    ft_printf("testing 's' specifier no buffer\n");
    ft_printf("%s%s\n", "abc", "def");
    ft_printf("1%s%s\n", "abc", "def");
    ft_printf("%s2%s\n", "abc", "def");
    ft_printf("%s%s\n", "abc", "def");
    ft_printf("%s2%s\n", "abc", "def");
    ft_printf("1%s2%s\n", "a", "b");

    ft_printf("testing 's' specifier buffer exact\n");
    ft_printf("123456%s\n", "abc");
    ft_printf("1234%s%s\n", "abc", "def");
    ft_printf("123%s5%s\n", "abc", "def");

    ft_printf("testing 's' specifier 1 over\n");
    ft_printf("1234567%s\n", "abc");
    ft_printf("12345%s%s\n", "abc", "def");
    ft_printf("1234%s5%s\n", "abc", "def");

    ft_printf("testing 's' specifier content buffer exact\n");
    ft_printf("123456%s\n", "abc");
    ft_printf("123%s%s\n", "abc", "def");
    ft_printf("12%s3%s\n", "abc", "def");

    ft_printf("testing 's' specifier content 1 over\n");
    ft_printf("1234567%s\n", "abc");
    ft_printf("1234%s%s\n", "abc", "def");
    ft_printf("123%s4%s\n", "abc", "def");

    ft_printf("testing 's' spesifier padding\n");
    ft_printf("%0s\n", "abc");
    ft_printf("%-s\n", "abc");
    ft_printf("%-0s\n", "abc");

    ft_printf("%5s\n", "abc");
    ft_printf("%9s\n", "abc");
    ft_printf("%10s\n", "abc");

    ft_printf("%-5s\n", "abc");
    ft_printf("%-9s\n", "abc");
    ft_printf("%-10s\n", "abc");

    ft_printf("%05s\n", "abc");
    ft_printf("%09s\n", "abc");
    ft_printf("%010s\n", "abc");

    ft_printf("%-05s\n", "abc");
    ft_printf("%-09s\n", "abc");
    ft_printf("%-010s\n", "abc");

    return 0;
}

int main(int ac, char **av) {
    (void)ac;    
    (void)av;

    test_printf();

    // DIR* dir = opendir("/home/odoo/42_school/ft_ls");
    // struct dirent* entry;

    // while ((entry = readdir(dir)) != NULL) {
    // }
    // for (int a = 0; a < 10; a++) {
    // }
    // ft_printf("1234567890987654321\0");

    // ft_printf("%-20s%-20s%-20s\n", "file1", "file2", "file3");
    // ft_printf("%-20s%-20s%-20s\n", "fileafr1", "file2", "file3");
    // ft_printf("%-20s%-20s%-20s\n", "file1", "file2", "file3");
    // ft_printf("%-20s%-20s%-20s\n", "file1", "fifawrle2", "file3");
    // ft_printf("%-20s%-20s%-20s\n", "filsfae1", "file2", "file3");
    // ft_printf("%-20s%-20s%-20s\n", "file1", "file2", "file3");
    // ft_printf("%-20s%-20s%-20s\n", "filadfe1", "file2", "fildafse3");
    // ft_printf("%-20s%-20s%-20s\n", "file1", "file2", "fildafe3");
    // ft_printf("%-20s%-20s%-20s\n", "file1", "fifadle2", "file3");
    // ft_printf("%-20s%-20s%-20s\n", "fiadfle1", "file2", "filafde3");
    // size_t rval2 = printf("%8d\n", 1234567);
    // printf("rval1 = %ld\n", rval1);
    // printf("rval2 = %ld\n", rval2);
    // printf("'%d'\n", add(1, 2));
    // ft_printf("'%5c%c'\n", 'a', 'b');
    //  '    a'
    return 1;
}