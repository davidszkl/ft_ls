# include "ft_ls.h"
# include "vector.h"
# include "directory.h"

static vector_s* make_entry_vector(DIR* dir) {
    vector_s* entry_vector = vector_make(25);

    if (!entry_vector) {
        return NULL;
    }
    struct dirent* entry;
    const int option_all = (&ft_ls)->selected_options & OPTION_ALL;

    while ((entry = readdir(dir)) != NULL) {
        if (
            ft_strcmp(entry->d_name, ".") == 0 ||
            ft_strcmp(entry->d_name, "..") == 0 ||
            (entry->d_name[0] == '.' && !(option_all))) {
            continue;
        }
        if (!vector_push(entry_vector, entry)) {
            vector_free(entry_vector);
        }
    }
    return entry_vector;
}

static void output_print(const vector_s* entry_vector, const char* parent_path, int first) {
    if (!first)
        write(1, "\n", 1);
    if ((&ft_ls)->selected_options & OPTION_RECURSIVE){
        ft_printf("%s:\n", parent_path);
    }
    if ((&ft_ls)->selected_options & OPTION_ALL) {
        ft_printf("\n.  ..  ");
    }
    for (size_t i = 0; i < entry_vector->size; i++) {
        ft_printf("%s  ", entry_vector->content[i]->d_name);
    }
    if (entry_vector->size) {
        write(1, "\n", 2);
    }
}

static vector_s* output_helper(DIR* dir, const char* parent_path, int first) {
    vector_s* entry_vector = make_entry_vector(dir);

    vector_sort(entry_vector);

    output_print(entry_vector, parent_path, first);

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
            // show_ino(&ft_ls.visited);
            if (has_ino(&ft_ls.visited, directories[i].ino) || ft_find_str(parent_path, "/dev/fd")) {
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
            if (add_ino(&ft_ls.visited, directories[i].ino))
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
