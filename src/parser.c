# include "ft_ls.h"
# include "parser.h"
# include "utils.h"
# include "directory.h"
# include "error.h"

static int set_option_short(const char option) {
    for (size_t i = 0; i < (&ft_ls)->options_count; i++) {
        if (option == (&ft_ls)->options[i].short_name) {
            (&ft_ls)->selected_options |= (&ft_ls)->options[i].val;
            return 0;
        }
    }
    return 1;
}

static int set_option_long(const char* option) {
    for (size_t i = 0; i < (&ft_ls)->options_count; i++) {
        if (ft_strcmp(option, (&ft_ls)->options[i].long_name) == 0) {
            (&ft_ls)->selected_options |= (&ft_ls)->options[i].val;
            return 0;
        }
    }
    return 1;
}

static int handle_value_option(char *option, const char* option_value) {
    for (size_t i = 0; i < ft_ls.options_count; i++) {
        if (ft_strcmp(ft_ls.options[i].long_name, option) == 0) {
            if (!option_value && ft_ls.options[i].values) {
                ft_dprintf(STDERR_FILENO, "ls: option '--%s' requires an argument\nTry 'ls --help' for more information.\n", option);
                return 1;
            }
            else if (option_value) {
                // value option #TODO
                ft_dprintf(STDERR_FILENO, "ls: options with values not yet supported '--%s'\nTry 'ls --help' for more information.\n", option);
                return 1;
            }
        }
    }
    return 0;
}

static int handle_option(const char* option_str) {
    // short option
    if (option_str[1] && option_str[1] != '-') {
        for (int i = 1; i < ft_strlen(option_str); i++) {\
            if (set_option_short(option_str[i]) != 0)
                return ft_dprintf(STDERR_FILENO, "ls: invalid option -- '%c'\nTry 'ls --help' for more information.\n", option_str[i]);
        }
        return 0;
    }
    // long option
    else if (option_str[1] && option_str[1] == '-') {
        // long option could be an option with values, check for '=' sign
        const char* option_value = ft_strchr('=', option_str);
        char *option = ft_strdup(&option_str[2], option_value - &option_str[2]);
        if (!option)
            return 1;
        if (handle_value_option(option, option_value))
            return ft_free(option, 1);
        
        if (set_option_long(&option_str[2]) != 0){
            ft_dprintf(STDERR_FILENO, "ls: unrecognized option '%s'\nTry 'ls --help' for more information.\n", option_str);
            return ft_free(option, 1);
        }
        ft_free(option, 0);
    }
    return 0;
}

// 0 no error, 1 error continue, 2+ error
static int handle_path(const char* path, dir_s* dirs, int path_count) {
    if (lstat(path, &dirs[path_count].stat) != 0) {
        dirs[path_count].error = make_error_str(NO_ACCESS, path);
        return dirs[path_count].error ? 0 : 1;
    }

    DIR* dir = opendir(path);
    if (!dir && errno) {
        dirs[path_count].error = make_error_str(NO_OPEN, path);
        return dirs[path_count].error ? 0 : 1;
    }
    
    char *name = ft_strtrim_one(path, '/');
    if (!name) {
        closedir(dir);
        return 2;
    }

    dirs[path_count].dir = dir;
    dirs[path_count].name = name;
    return 0;
}

static int init_dirs(dir_s* dirs) {
    char cwd[PATH_MAX];
    if (!getcwd(cwd, PATH_MAX))
        return 1;
    if (lstat(".", &dirs[0].stat))
        return 1;
    dirs[0].name = ft_strdup(".", 1);
    if (!dirs[0].name)
        return 1;
    dirs[0].dir = opendir(cwd);
    if (!dirs[0].dir) {
        free(dirs[0].name);
        return 1;
    }
    dirs[0].error = NULL;
    return 0;
}

static int set_arguments_after_parse(dir_s* dirs) {
    if (dirs->count > 1 || (&ft_ls)->selected_options & OPTION_RECURSIVE)
        ft_ls.show_headers = 1;
    return 0;
}

static int compare_time(dir_s* a, dir_s* b) {
    if (a->stat.st_mtim.tv_sec != b->stat.st_mtim.tv_sec)
        return a->stat.st_mtim.tv_sec < b->stat.st_mtim.tv_sec;
    if (a->stat.st_mtim.tv_nsec != b->stat.st_mtim.tv_nsec)
        return a->stat.st_mtim.tv_nsec < b->stat.st_mtim.tv_nsec;
    return ft_strcmp_dot(a->name, b->name) > 0;
}

static int compare_helper(dir_s* a, dir_s* b) {
    // lstat failed because of no permissions, sort in alphabetical order only.
    if (a->error || b->error) {
        return ft_strcmp_dot(a->name, b->name) > 0;
    }
    // normal case
    if (ft_ls.selected_options & OPTION_SORT_TIME) {
        return compare_time(a, b);
    } else {
        return ft_strcmp_dot(a->name, b->name) > 0;
    }
}

static void sort_compare(dir_s* a, dir_s* b) {
    dir_s small;
    dir_s big;
    int comp = compare_helper(a, b) > 0;
    int reverse_sort = ft_ls.selected_options & OPTION_REVERSE_SORT;
    small = comp ? *a : *b;
    big = comp ? *b : *a;
    *a = reverse_sort ? small : big;
    *b = reverse_sort ? big : small;
}

static int sort_dirs(dir_s* dirs, size_t count) {
    for (size_t i = 0; i < count; i++) {
        for (size_t j = i + 1; j < count; j++) {
            sort_compare(&dirs[i], &dirs[j]);
        }
    }
    return 0;
}

int parse_arguments(int ac, char** av) {
    dir_s* dirs;
    int path_count = 0;
    int path_args = 0;

    // Most of the arguments to the program should be paths to list.
    dirs = ft_malloc_zero(sizeof(dir_s) * (ac));
    if (!dirs)
        return 1;

    for (int argc = 1; argc < ac; argc++) {
        // for every argument, check if it's an option ( starts with '-') or a path
        if (av[argc] && av[argc][0] && av[argc][0] == '-') {
            if (handle_option(av[argc]) != 0)
                return ft_free(dirs, 1);
        } else {
            path_args++;
            if (handle_path(av[argc], dirs, path_count))
                return ft_free(dirs, 1);
            path_count++;
        }
    }
    if (path_args == 0) {
        if (init_dirs(dirs))
            return ft_free(dirs, 1);
        path_count++;
    }
    sort_dirs(dirs, path_count);
    dirs->count = path_count;
    (&ft_ls)->dirs = dirs;
    return set_arguments_after_parse(dirs);
}
