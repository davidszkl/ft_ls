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

static void output_print(const vector_s* entry_vector, const char* path) {
    if ((&ft_ls)->selected_options & OPTION_RECURSIVE){
        ft_printf("%s/:\n", path);
    }
    if ((&ft_ls)->selected_options & OPTION_ALL) {
        ft_printf(". .. ");
    }
    for (size_t i = 0; i < entry_vector->size; i++) {
        ft_printf("%s ", entry_vector->content[i]->d_name);
    }
    write(1, "\n\n", 2);
}

static vector_s* output_helper(DIR* dir, const char* path) {
    vector_s* entry_vector = make_entry_vector(dir);

    vector_sort(entry_vector);

    output_print(entry_vector, path);

    return entry_vector;
}

void output(DIR* dir, const char* path) {
    vector_s* entry_vector = output_helper(dir, path);
    if (!entry_vector)
        return;

    dir_s* directories = get_directories(entry_vector);
    if (!directories) {
        vector_free(entry_vector);
        return;
    }

    if ((&ft_ls)->selected_options & OPTION_RECURSIVE) {
        size_t i = 0;
        while (directories[i].dir != NULL) {
            output(directories[i].dir, directories[i].name);
            i++;
        }
    }

}
