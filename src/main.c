# include <stdlib.h>
# include <stdio.h>
# include "main.h"
# include "utils.h"

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

ft_ls_s ft_ls = {
    .options_count = 5,
    .options = {
        [0] = { .val = OPTION_LONG, .short_name = 'l', .long_name = NULL, .values = NULL },
        [1] = { .val = OPTION_RECURSIVE, .short_name = 'R', .long_name = "recursive", .values = NULL },
        [2] = { .val = OPTION_ALL, .short_name = 'a', .long_name = "all", .values = NULL },
        [3] = { .val = OPTION_REVERSE_SORT, .short_name = 'r', .long_name = "reverse", .values = NULL },
        [4] = { .val = OPTION_SORT_TIME, .short_name = 't', .long_name = "time", .values = NULL}
    }
};

static int init_ft_ls() {
    ft_ls.options[4].values = malloc(6 * sizeof(char *));
    if (ft_ls.options[4].values == NULL)
        return 1;
    ft_ls.options[4].values[0] = "atime";
    ft_ls.options[4].values[1] = "access";
    ft_ls.options[4].values[2] = "use";
    ft_ls.options[4].values[3] = "ctime";
    ft_ls.options[4].values[4] = "status";
    ft_ls.options[4].values[5] = "birth";
    return 0;
}

int main(int ac, char** av) {
    // test_printf();
    if (init_ft_ls())
        return 1;
    if (parse_arguments(ac, av) != 0)
        return ft_free(ft_ls.options[4].values, 1);

    if (!init_visited(&ft_ls.visited))
        dir_free(ft_ls.dirs, 1);

    for (size_t i = 0; i < ft_ls.dirs->count; i++) {
        if (ft_ls.dirs[i].error) {
            write(STDERR_FILENO, ft_ls.dirs[i].error, ft_strlen(ft_ls.dirs[i].error));
            continue;
        }
        if (i > 0)
            write(STDOUT_FILENO, "\n", 1);
        if (ft_find_str(ft_ls.dirs[i].name, "/dev/fd"))
            continue;
        if (add_ino(&ft_ls.visited, ft_ls.dirs[i].stat.st_ino))
            break;
        ft_ls.parent_path = ft_ls.dirs[i].name;
        if (output(ft_ls.dirs[i].dir, ft_ls.dirs[i].name, 1) != 0)
            break;
    }
    
    free(ft_ls.visited.ino);
    free(ft_ls.options[4].values);
    return dir_free(ft_ls.dirs, 0);
}
