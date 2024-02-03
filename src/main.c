# include <stdlib.h>
# include <stdio.h>
# include "ft_ls.h"
# include "ft_printf.h"
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

// DIR** _get_target_dirs(int ac, char** av) {
//     dirs[0] = opendir(cwd);
//     for (int i = 0; i < ac; i++) {
//         dirs[i] = opendir(av[i]);
//         if (!dirs[i]) {
            
//         }
//     }

//     return dirs;
// }

int set_option_short(const char option, ft_ls_s* ft_ls) {
    for (int i = 0; i < ft_ls->options_count; i++) {
        if (option == ft_ls->options[i].short_name) {
            ft_ls->selected_options |= ft_ls->options[i].val;
            return 0;
        }
    }
    return 1;
}

int set_option_long(const char* option, ft_ls_s* ft_ls) {
    for (int i = 0; i < ft_ls->options_count; i++) {
        if (ft_strcmp(option, ft_ls->options[i].long_name) == 0) {
            ft_ls->selected_options |= ft_ls->options[i].val;
            return 0;
        }
    }
    return 1;
}

int handle_option(const char* option_str, ft_ls_s* ft_ls) {
    // short option
    if (option_str[1] && option_str[1] != '-') {
        for (int i = 1; i < ft_strlen(option_str); i++) {\
            // find if it's one of the options available, if not error message and exit;
            if (set_option_short(option_str[i], ft_ls) != 0)
                return ft_printf("ft_ls: invalid option -- '%c'\nTry 'ft_ls --help' for more information.\n", option_str[i]);
        }
        return 0;
    }
    // long option
    else if (option_str[1] && option_str[1] == '-') {
        // long option could be an option with values, check for '=' sign
        const char* option_value = ft_strchr('=', &option_str[2]);
        if (option_value) {  // #Maybe bug: what if ft_strchr just failed ?
            // value option #TODO
            ft_printf("ft_ls: options with values not yet supported -- '%s'\nTry 'ft_ls --help' for more information.\n", &option_str[2]);
            return 1;
        }
        if (set_option_long(&option_str[2], ft_ls) != 0){
            ft_printf("ft_ls: unrecognized option -- '%s'\nTry 'ft_ls --help' for more information.\n", &option_str[2]);
            return 1;
        }
    }
    return 0;
}

int handle_path(const char* path, DIR** dirs, int path_count, struct stat* statbuf) {
    if (stat(path, statbuf) != 0) {
        ft_printf("ft_ls: cannot access '%s': No such file or directory", path);
        return 1;
    }

    dirs[path_count] = opendir(path);
    if (!dirs[path_count])
        return 1;

    return 0;
}

int parse_arguments(int ac, char** av, ft_ls_s* ft_ls) {
    DIR** dirs = NULL;
    struct stat statbuf;
    int path_count = 0;

    // Most of the arguments to the program should be paths to list.
    dirs = malloc(sizeof(DIR*) * (ac));
    if (!dirs)
        return 1;
    ft_memset(dirs, 0, sizeof(DIR*) * (ac));

    for (int argc = 1; argc < ac; argc++) {
        // for every argument, check if it's an option ( starts with '-') or a path
        if (av[argc] && av[argc][0] && av[argc][0] == '-') {
            if (handle_option(av[argc], ft_ls) != 0)
                return ft_free(dirs, 1);
        } else {
            if (handle_path(av[argc], dirs, path_count, &statbuf) != 0)
                return ft_free(dirs, 1);
            path_count++;
        }
    }
    if (!path_count++) {
        char cwd[PATH_MAX];
        if (!getcwd(cwd, PATH_MAX))
            return ft_free(dirs, 1);

        dirs[0] = opendir(cwd);
        if (!dirs[0])
            return ft_free(dirs, 1);
    }
    ft_ls->dirs = dirs;
    ft_ls->dirs_count = path_count;
    return 0;
}

int main(int ac, char** av) {
    // test_printf();
    ft_ls_s ft_ls = {
        .options_count = 5,
        .options = {
            [0] = { .val = OPTION_LONG, .short_name = 'l', .long_name = NULL, .values = NULL },
            [1] = { .val = OPTION_RECURSIVE, .short_name = 'R', .long_name = "recursive", .values = NULL },
            [2] = { .val = OPTION_ALL, .short_name = 'a', .long_name = "all", .values = NULL },
            [3] = { .val = OPTION_REVERSE_SORT, .short_name = 'r', .long_name = "reverse", .values = NULL },
            [4] = { .val = OPTION_SORT_TIME, .short_name = 't', .long_name = NULL, .values = NULL }
        }
    };
 
    if (parse_arguments(ac, av, &ft_ls) != 0) {
        return 1;
    }

    ft_printf("%d\n", ft_ls.selected_options);
    struct dirent* entry;
    for (int i = 0; i < ft_ls.dirs_count; i++) {
        while ((entry = readdir(ft_ls.dirs[i])) != NULL) {
            ft_printf("%s\n", entry->d_name);
        }        
    }
    return 0;
}
