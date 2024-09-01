# include "ft_ls.h"
# include "vector.h"


void output(DIR* dir) {
    vector_s* entry_vector = vector_make(25);
    if (!entry_vector) {
        return;
    }
    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.' && !((&ft_ls)->selected_options && OPTION_ALL)) {
            continue;
        }
        if (!vector_push(entry_vector, entry)) {
            vector_free(entry_vector);
        }
    }
    vector_sort(entry_vector);
    for (size_t i = 0; i < entry_vector->size; i++) {
        entry = entry_vector->content[i];
        ft_printf("%s\n", entry->d_name);
    }
}
