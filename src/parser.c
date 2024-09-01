# include "ft_ls.h"
# include "parser.h"
# include "utils.h"

int set_option_short(const char option) {
    for (int i = 0; i < (&ft_ls)->options_count; i++) {
        if (option == (&ft_ls)->options[i].short_name) {
            (&ft_ls)->selected_options |= (&ft_ls)->options[i].val;
            return 0;
        }
    }
    return 1;
}

int set_option_long(const char* option) {
    for (int i = 0; i < (&ft_ls)->options_count; i++) {
        if (ft_strcmp(option, (&ft_ls)->options[i].long_name) == 0) {
            (&ft_ls)->selected_options |= (&ft_ls)->options[i].val;
            return 0;
        }
    }
    return 1;
}

int handle_option(const char* option_str) {
    // short option
    if (option_str[1] && option_str[1] != '-') {
        for (int i = 1; i < ft_strlen(option_str); i++) {\
            // find if it's one of the options available, if not error message and exit;
            if (set_option_short(option_str[i]) != 0)
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
        if (set_option_long(&option_str[2]) != 0){
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

int parse_arguments(int ac, char** av) {
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
            if (handle_option(av[argc]) != 0)
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
    (&ft_ls)->dirs = dirs;
    (&ft_ls)->dirs_count = path_count;
    return 0;
}
