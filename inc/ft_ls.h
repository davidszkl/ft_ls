# pragma once
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <linux/limits.h>
# include <errno.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "ft_printf.h"

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
    char* error;
    struct stat stat;
    size_t count;
} dir_s;

typedef struct visited_ino_t {
    ino_t* ino;
    size_t size;
    size_t capacity;
} visited_ino_s;

typedef struct ft_ls_t {
    int selected_options;
    size_t options_count;
    int show_headers;
    dir_s* dirs;
    options_s options[5];
    visited_ino_s visited;
    char* parent_path;
} ft_ls_s;

typedef struct output_long_t {
    char* perms;
    nlink_t links;
    char* user;
    char* group;
    off_t size;
    char* datetime;
    char* fname;
    size_t count;
} output_long_s;

extern ft_ls_s ft_ls;