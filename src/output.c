# include "output.h"

static vector_s* make_entry_vector(DIR* dir) {
    const int option_all = (&ft_ls)->selected_options & OPTION_ALL;
    vector_s* entry_vector = vector_make(25);
    struct dirent* entry;

    if (!entry_vector) {
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if ((is_dot_folder(entry->d_name) || is_hidden_folder(entry->d_name)) && !option_all)
            continue;
        if (!vector_push(entry_vector, entry, ft_ls.parent_path)) {
            vector_free(entry_vector);
            return NULL;
        }
    }
    return entry_vector;
}

static char* type_perm_string(dirent_stat_s* stat) {
    size_t size = stat->error ? 2 : 11;
    char* str = malloc(sizeof(char) * size);
    if (!str)
        return NULL;
    mode_t mode = stat->stat.st_mode;

    // file type
    if ((mode && S_ISREG(mode)) || (stat->error && stat->elem->d_type == DT_REG)) {
        str[0] = '-';
    } else if ((mode && S_ISDIR(mode)) || (stat->error && stat->elem->d_type == DT_DIR)) {
        str[0] = 'd';
    } else if ((mode && S_ISCHR(mode)) || (stat->error && stat->elem->d_type == DT_CHR)) {
        str[0] = 'c';
    } else if ((mode && S_ISBLK(mode)) || (stat->error && stat->elem->d_type == DT_BLK)) {
        str[0] = 'b';
    } else if ((mode && S_ISFIFO(mode)) || (stat->error && stat->elem->d_type == DT_FIFO)) {
        str[0] = 'p';
    } else if ((mode && S_ISLNK(mode)) || (stat->error && stat->elem->d_type == DT_LNK)) {
        str[0] = 'l';
    } else if ((mode && S_ISSOCK(mode)) || (stat->error && stat->elem->d_type == DT_SOCK)) {
        str[0] = 's';
    } else {
        str[0] = '?';
    }

    if (stat->error) {
        str[1] = '\0';
        return str;
    }

    // user permissions
    str[1] = mode & S_IRUSR ? 'r' : '-';
    str[2] = mode & S_IWUSR ? 'w' : '-';
    str[3] = mode & S_IXUSR ? 'x' : '-';

    // group permissions
    str[4] = mode & S_IRGRP ? 'r' : '-';
    str[5] = mode & S_IWGRP ? 'w' : '-';
    str[6] = mode & S_IXGRP ? 'x' : '-';

    // other permissions
    str[7] = mode & S_IROTH ? 'r' : '-';
    str[8] = mode & S_IWOTH ? 'w' : '-';
    str[9] = mode & S_IXOTH ? 'x' : '-';

    // sticky bit
    str[9] = mode & S_ISVTX ? 't' : str[9];

    str[10] = '\0';
    return str;
}

static char* user_string(uid_t uid) {
    struct passwd* passwd = getpwuid(uid);
    if (!passwd)
        return NULL;
    return ft_strdup(passwd->pw_name, -1);
}

static char* group_string(gid_t gid) {
    struct group* group = getgrgid(gid);
    if (!group)
        return NULL;
    return ft_strdup(group->gr_name, -1);
}

static char* time_string(time_t* time) {
    char* strtime = ctime(time);
    if (!strtime)
        return NULL;
    char* rval = ft_substr(strtime, 4, ft_strlen(strtime) - 9);
    return rval;
}

static char* symbolic_file_string(dirent_stat_s* dir) {
    char* rval = NULL;
    size_t link_size = ft_strlen(dir->elem->d_name);
    rval = malloc(sizeof(char*) * (link_size + 4 + dir->stat.st_size + 1));
    if (!rval)
        return NULL;
    ft_memset(rval, 0, link_size + 4 + dir->stat.st_size + 1);
    ft_memcpy(rval, dir->elem->d_name, link_size);
    ft_memcpy(rval + link_size, " -> ", 4);
    char *complete_link_name = ft_strjoin_path(ft_ls.parent_path, dir->elem->d_name);
    if (!complete_link_name) {
        free(rval);
        return NULL;
    }
    if (readlink(complete_link_name, rval + link_size + 4, dir->stat.st_size) == -1) {
        free(rval);
        free(complete_link_name);
        return NULL;
    }
    rval[link_size + 4 + dir->stat.st_size + 1] = '\0';
    free(complete_link_name);
    return rval;
}

static char* file_string(dirent_stat_s* dir) {
    char* rval = NULL;
    if (is_symbolic_link(&dir->stat)) {
        rval = symbolic_file_string(dir);
    } else {
        rval = ft_strdup(dir->elem->d_name, -1);
        if (!rval)
            return NULL;
    }
    return rval;
}

static output_long_s* create_output_long(dirent_stat_s* stat) {
    output_long_s* output_long = ft_malloc_zero(sizeof(output_long_s));
    if (!output_long)
        return NULL;

    output_long->perms = type_perm_string(stat);
    if (!output_long->perms)
        return NULL;

    if (stat->error) {
        size_t len = ft_strlen(stat->elem->d_name);
        output_long->error = malloc(sizeof(char) * (31 + len + 1));
        if (!output_long->error) {
            ft_free_output_long(output_long, 1);
            return NULL;
        }
        ft_memcpy(output_long->error, "????????? ? ? ? ?            ? ", 31);          
        ft_memcpy(output_long->error + 31, stat->elem->d_name, len);
        output_long->error[31 + len] = '\0';
        return output_long;
    }

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

    output_long->fname = file_string(stat);
    if (!output_long->fname) {
        ft_free_output_long(output_long, 1);
        return NULL;
    }

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
        if (
            (is_dot_folder(entry_vector->content[i]->elem->d_name) || is_hidden_folder(entry_vector->content[i]->elem->d_name))
            && !option_all
        )
            continue;
        *total_blocks += entry_vector->content[i]->stat.st_blocks / 2; // ls displays by default blocks of size 1024;
        output_info[dir_idx] = create_output_long(entry_vector->content[i]);
        if (!output_info[dir_idx++]) {
            ft_free_output_long_tab(output_info, 1);
            return NULL;
        }
    }
    
    if (entry_vector->size == 0 || dir_idx == 0) { // at least one node is needed to store the count;
        output_info[0] = ft_malloc_zero(sizeof(output_long_s));
        if (!output_info[0]) {
            ft_free_output_long_tab(output_info, 1);
            return NULL;
        }
        // output_info[0]->perms = NULL;
        // output_info[0]->datetime = NULL;
        // output_info[0]->fname = NULL;
        // output_info[0]->user = NULL;
        // output_info[0]->group = NULL;
    }
    output_info[0]->count = dir_idx;
    return output_info;
}

static int set_max_widths(int* widths, output_long_s** output_info) {
    widths[0] = 10;
    widths[5] = 12;
    for (size_t i = 0; i < output_info[0]->count; i++) {
        if (output_info[i]->error)
            continue;
        widths[1] = max(widths[1], numberlen(output_info[i]->links));
        widths[2] = max(widths[2], ft_strlen(output_info[i]->user));
        widths[3] = max(widths[3], ft_strlen(output_info[i]->group));
        widths[4] = max(widths[4], numberlen(output_info[i]->size));
    }
    return 0;
}

static int print_output_long(output_long_s** output_info, int* widths, size_t total_blocks) {
    ft_dprintf(STDOUT_FILENO, "total %d\n", total_blocks);
    char* format_string = NULL;
    ft_sprintf(&format_string, "%%-%ds %%-%dd %%-%ds %%-%ds %%%dd %%%ds %%-s\n", widths[0], widths[1], widths[2], widths[3], widths[4], widths[5]);
    for (size_t i = 0; i < output_info[0]->count; i++) {
        if (output_info[i]->error) {
            if (ft_dprintf(STDERR_FILENO, "%c%s\n", output_info[i]->perms[0], output_info[i]->error) == -1)
                return ft_free(format_string, 1);
            continue;
        }
        if (ft_dprintf(STDOUT_FILENO, format_string, output_info[i]->perms, output_info[i]->links, output_info[i]->user, output_info[i]->group, output_info[i]->size, output_info[i]->datetime, output_info[i]->fname) == -1) {
            return ft_free(format_string, 1);
        }
    }
    free(format_string);
    return 0;
}

static int output_print_long(const vector_s* entry_vector, int first) {
    if (!first)
        write(STDOUT_FILENO, "\n", 1);
    if ((&ft_ls)->show_headers){
        ft_dprintf(STDOUT_FILENO, "%s:\n", ft_ls.parent_path);
    }
    size_t total_blocks = 0;
    output_long_s** output_info = make_output_long_info(entry_vector, &total_blocks);
    if (!output_info)
        return ft_free_output_long_tab(output_info, 1);

    int widths[6] = {0};
    if (set_max_widths(widths, output_info))
        return ft_free_output_long_tab(output_info, 1);
    
    print_output_long(output_info, widths, total_blocks);
    return ft_free_output_long_tab(output_info, 0);
}

static char* compute_buffer_len(const vector_s* entry_vector, const int option_all, size_t* str_len) {
    for (size_t i = 0; i < entry_vector->size; i++) {
        if (
            (is_dot_folder(entry_vector->content[i]->elem->d_name) || is_hidden_folder(entry_vector->content[i]->elem->d_name))
            && !option_all
        )
            continue;
        *str_len += ft_strlen(entry_vector->content[i]->elem->d_name) + 2;
    }
    char* buffer = malloc(sizeof(char) * (*str_len + 1));
    if (!buffer)
        return NULL;

    return buffer;
}

static int fill_buffer(const vector_s* entry_vector, const int option_all, char* buffer, size_t* real_count) {
    size_t idx = 0;
    for (size_t i = 0; i < entry_vector->size; i++) {
        if (
            (is_dot_folder(entry_vector->content[i]->elem->d_name) || is_hidden_folder(entry_vector->content[i]->elem->d_name))
            && !option_all
        )
            continue;
        size_t len = ft_strlen(entry_vector->content[i]->elem->d_name);
        if (*real_count > 0) {
            buffer[idx++] = ' ';
            buffer[idx++] = ' ';
        }
        ft_memcpy(&buffer[idx], entry_vector->content[i]->elem->d_name, len);
        idx += len;
        *real_count += 1;
    }

    buffer[idx] = '\0';
    return idx;
}

static int output_print_normal(const vector_s* entry_vector, int first) {
    const int option_all = (&ft_ls)->selected_options & OPTION_ALL;
    if (!first)
        write(STDOUT_FILENO, "\n", 1);
    if ((&ft_ls)->show_headers){
        ft_dprintf(STDOUT_FILENO, "%s:\n", ft_ls.parent_path);
    }
    size_t real_count = 0;
    size_t str_len = 0;
    char* buffer = compute_buffer_len(entry_vector, option_all, &str_len);
    if (!buffer)
        return 1;

    size_t idx = fill_buffer(entry_vector, option_all, buffer, &real_count);

    write(STDOUT_FILENO, buffer, idx);
    if (real_count) {
        write(STDOUT_FILENO, "\n", 1);
    }
    return ft_free(buffer, 0);
}

static int output_print(const vector_s* entry_vector, int first) {
    if ((&ft_ls)->selected_options & OPTION_LONG){
        if (output_print_long(entry_vector, first))
            return 1;
    } else {
        if (output_print_normal(entry_vector, first))
            return 1;
    }
    return 0;
}

static vector_s* output_helper(DIR* dir, int first) {
    vector_s* entry_vector = make_entry_vector(dir);
    if (!entry_vector)
        return NULL;

    vector_sort(entry_vector);

    if (output_print(entry_vector, first))
        return NULL;

    return entry_vector;
}

int output(DIR* dir, int first) {
    char* previous_path = ft_ls.parent_path;
    vector_s* entry_vector = output_helper(dir, first);
    if (!entry_vector)
        return 1;

    dir_s* directories = get_directories(entry_vector);
    if (!directories) {
        vector_free(entry_vector);
        return 1;
    }

    if (directories->count > 0 && (&ft_ls)->selected_options & OPTION_RECURSIVE) {
        for (size_t i = 0; i < directories->count; i++) {
            if (
                has_ino(&ft_ls.visited, directories[i].stat.st_ino) ||
                ft_find_str(ft_ls.parent_path, "/dev/fd") ||
                is_dot_folder(directories[i].name) ||
                is_symbolic_link(&directories[i].stat)
                ) {
                continue;
            }
            if (directories[i].error) {
                write(STDERR_FILENO, directories[i].error, ft_strlen(directories[i].error));
                    continue;
            }

            char* current_path = ft_strjoin_path(ft_ls.parent_path, directories[i].name);
            if (!current_path) {
                vector_free(entry_vector);
                return dir_free(directories, 1);
            }
            if (add_ino(&ft_ls.visited, directories[i].stat.st_ino))
                return dir_free(directories, 1);
            ft_ls.parent_path = current_path;
            if (output(directories[i].dir, 0) != 0) {
                free((char*)current_path);
                vector_free(entry_vector);
                return dir_free(directories, 1);
            }
            ft_ls.parent_path = previous_path;

            ft_ls.visited.size--;
            free((char*)current_path);
        }
    }

    vector_free(entry_vector);
    return dir_free(directories, 0);
}
