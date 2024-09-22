# include "ft_ls.h"
# include "vector.h"
# include "directory.h"

static int is_dot_folder(char* name) {
    return ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0;
}

// static int is_hidden_folder(char* name) {
//     return name[0] && name[0] == '.' && name[1] && name[1] != '.';
// }

static vector_s* make_entry_vector(DIR* dir, const char* parent_path) {
    vector_s* entry_vector = vector_make(25);
    struct dirent* entry;

    if (!entry_vector) {
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!vector_push(entry_vector, entry, parent_path)) {
            vector_free(entry_vector);
            return NULL;
        }
    }
    return entry_vector;
}

static char* type_perm_string(__mode_t mode) {
    char* str = malloc(sizeof(char) * 11);
    if (!str)
        return NULL;

    // file type
    if (S_ISREG(mode)) {
        str[0] = '-';
    } else if (S_ISDIR(mode)) {
        str[0] = 'd';
    } else if (S_ISCHR(mode)) {
        str[0] = 'c';
    } else if (S_ISBLK(mode)) {
        str[0] = 'b';
    } else if (S_ISFIFO(mode)) {
        str[0] = 'p';
    } else if (S_ISLNK(mode)) {
        str[0] = 'l';
    } else if (S_ISSOCK(mode)) {
        str[0] = 's';
    } else {
        str[0] = '?';
    }

    // user permissions
    str[1] = mode & S_IRUSR ? 'r' : '-';
    str[2] = mode & S_IWUSR ? 'w' : '-';
    str[3] = mode & S_IXUSR ? 'x' : '-';

    // Group permissions
    str[4] = mode & S_IRGRP ? 'r' : '-';
    str[5] = mode & S_IWGRP ? 'w' : '-';
    str[6] = mode & S_IXGRP ? 'x' : '-';

    // Other permissions
    str[7] = mode & S_IROTH ? 'r' : '-';
    str[8] = mode & S_IWOTH ? 'w' : '-';
    str[9] = mode & S_IXOTH ? 'x' : '-';

    str[10] = '\0';
    return str;
}

static char* user_string(uid_t uid) {
    struct passwd* passwd = getpwuid(uid);
    if (!passwd)
        return NULL;
    return passwd->pw_name;
}

static char* group_string(gid_t gid) {
    struct group* group = getgrgid(gid);
    if (!group)
        return NULL;
    return group->gr_name;
}

static char* time_string(time_t* time) {
    char* strtime = ctime(time);
    if (!strtime)
        return NULL;
    char* rval = ft_substr(strtime, 4, ft_strlen(strtime) - 9);
    return rval;
}

static output_long_s* create_output_long(dirent_stat_s* stat) {
    output_long_s* output_long = malloc(sizeof(output_long_s));
    if (!output_long)
        return NULL;

    output_long->perms = type_perm_string(stat->stat.st_mode);
    if (!output_long->perms)
        return NULL;

    output_long->links = stat->stat.st_nlink;

    output_long->user = user_string(stat->stat.st_uid);
    if (!output_long->user) {
        ft_free_output_long(output_long, 1);
        return NULL;
    }

    output_long->group = group_string(stat->stat.st_uid);
    if (!output_long->group) {
        ft_free_output_long(output_long, 1);
        return NULL;
    }

    output_long->size = stat->stat.st_size;

    output_long->datetime = time_string(&stat->stat.st_mtime);
    if (!output_long->datetime) {
        ft_free_output_long(output_long, 1);
        return NULL;
    }
    output_long->fname = stat->elem->d_name;

    return output_long;
}

static output_long_s** make_output_long_info(const vector_s* entry_vector, size_t* total_blocks) {
    const int option_all = (&ft_ls)->selected_options & OPTION_ALL;
    output_long_s** output_info = malloc(sizeof(output_long_s*) * (entry_vector->size + 1));
    if (!output_info)
        return NULL;
    ft_memset(output_info, 0, sizeof(output_long_s*) * (entry_vector->size + 1));

    size_t dir_idx = 0;
    for (size_t i = 0; i < entry_vector->size; i++) {
        if (is_dot_folder(entry_vector->content[i]->elem->d_name) && !option_all)
            continue;
        *total_blocks += entry_vector->content[i]->stat.st_blocks / 2; // ls displays by default blocks of size 1024;
        output_info[dir_idx] = create_output_long(entry_vector->content[i]);
        if (!output_info[dir_idx++]) {
            ft_free_output_long_tab(output_info, 1);
            return NULL;
        }
    }
    
    if (entry_vector->size == 0) { // at least one node is needed to store the count;
        output_info[0] = malloc(sizeof(output_long_s));
        if (!output_info[0]) {
            ft_free_output_long_tab(output_info, 1);
            return NULL;
        }
        output_info[0]->perms = NULL;
        output_info[0]->datetime = NULL;
    }
    output_info[0]->count = dir_idx;
    return output_info;
}

static int set_max_widths(int* widths, output_long_s** output_info) {
    widths[0] = 11;
    widths[5] = 13;
    for (size_t i = 0; i < output_info[0]->count; i++) {
        widths[1] = max(widths[1], numberlen(output_info[i]->links));
        widths[2] = max(widths[2], ft_strlen(output_info[i]->user));
        widths[3] = max(widths[3], ft_strlen(output_info[i]->group));
        widths[4] = max(widths[4], numberlen(output_info[i]->size));
    }
    return 0;
}

static int print_output_long(output_long_s** output_info, int* widths, size_t total_blocks) {
    ft_printf("total %d\n", total_blocks);
    char* format_string = NULL;
    ft_sprintf(&format_string, "%%%ds %%%dd %%%ds %%%ds %%%dd %%%ds %%s\n", widths[0], widths[1], widths[2], widths[3], widths[4], widths[5]);
    for (size_t i = 0; i < output_info[0]->count; i++) {
        if (ft_printf(format_string, output_info[i]->perms, output_info[i]->links, output_info[i]->user, output_info[i]->group, output_info[i]->size, output_info[i]->datetime, output_info[i]->fname) == -1) {
            free(format_string);
            return 1;
        }
    }
    free(format_string);
    return 0;
}

static int output_print_long(const vector_s* entry_vector, const char* parent_path, int first) {
    if (!first)
        write(1, "\n", 1);
    if ((&ft_ls)->show_headers){
        ft_printf("%s:\n", parent_path);
    }
    size_t total_blocks = 0;
    output_long_s** output_info = make_output_long_info(entry_vector, &total_blocks);
    if (!output_info)
        return ft_free_output_long_tab(output_info, 1);

    int widths[6] = {0};
    if (set_max_widths(widths, output_info))
        return ft_free_output_long_tab(output_info, 1);
    
    print_output_long(output_info, widths, total_blocks);
    if (output_info[0]->count) {
        write(1, "\n", 1);
    }

    return ft_free_output_long_tab(output_info, 0);
}

static int output_print_normal(const vector_s* entry_vector, const char* parent_path, int first) {
    const int option_all = (&ft_ls)->selected_options & OPTION_ALL;
    if (!first)
        write(1, "\n", 1);
    if ((&ft_ls)->show_headers){
        ft_printf("%s:\n", parent_path);
    }
    size_t real_count = 0;
    for (size_t i = 0; i < entry_vector->size; i++) {
        if (is_dot_folder(entry_vector->content[i]->elem->d_name) && !option_all)
            continue;
        ft_printf("%s  ", entry_vector->content[i]->elem->d_name);
        real_count++;
    }
    if (real_count) {
        write(1, "\n", 1);
    }
    return 0;
}

static int output_print(const vector_s* entry_vector, const char* parent_path, int first) {
    if ((&ft_ls)->selected_options & OPTION_LONG){
        if (output_print_long(entry_vector, parent_path, first))
            return 1;
    } else {
        if (output_print_normal(entry_vector, parent_path, first))
            return 1;
    }
    return 0;
}

static vector_s* output_helper(DIR* dir, const char* parent_path, int first) {
    vector_s* entry_vector = make_entry_vector(dir, parent_path);
    if (!entry_vector)
        return NULL;

    vector_sort(entry_vector);

    if (output_print(entry_vector, parent_path, first))
        return NULL;

    return entry_vector;
}

int output(DIR* dir, const char* parent_path, int first) {
    vector_s* entry_vector = output_helper(dir, parent_path, first);
    if (!entry_vector)
        return 1;

    dir_s* directories = get_directories(entry_vector, parent_path);
    if (!directories) {
        vector_free(entry_vector);
        return 1;
    }

    if (directories->count > 0 && (&ft_ls)->selected_options & OPTION_RECURSIVE) {
        const char* current_path = NULL;
        for (size_t i = 0; i < directories->count; i++) {
            if (
                has_ino(&ft_ls.visited, directories[i].stat.st_ino) ||
                ft_find_str(parent_path, "/dev/fd") ||
                is_dot_folder(directories[i].name)
                ) {
                continue;
            }
            if (directories[i].error) {
                write(1, directories[i].error, ft_strlen(directories[i].error));
                continue;
            }

            current_path = ft_strjoin_path(parent_path, directories[i].name);
            if (!current_path) {
                vector_free(entry_vector);
                return dir_free(directories, 1);
            }
            if (add_ino(&ft_ls.visited, directories[i].stat.st_ino))
                return dir_free(directories, 1);
            if (output(directories[i].dir, current_path, 0) != 0) {
                free((char*)current_path);
                vector_free(entry_vector);
                return dir_free(directories, 1);
            }

            ft_ls.visited.size--;
            free((char*)current_path);
        }
    }

    vector_free(entry_vector);
    return dir_free(directories, 0);
}
