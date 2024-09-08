# pragma once
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <linux/limits.h>
# include <errno.h>
# include "ft_printf.h"
# include "utils.h"

// options
# define OPTION_LONG 1
# define OPTION_RECURSIVE 2
# define OPTION_ALL 4
# define OPTION_REVERSE_SORT 8
# define OPTION_SORT_TIME 16

typedef struct options_s {
    int val;
    char short_name;
    char* long_name;
    char** values;  // for options like format or sort that can have values specified
} options_s;

typedef struct dir_t {
    DIR* dir;
    char* name;
    size_t count;
} dir_s;

typedef struct ft_ls_s {
    int selected_options;
    int options_count;
    dir_s* dirs;
    options_s options[5];
} ft_ls_s;

extern ft_ls_s ft_ls;