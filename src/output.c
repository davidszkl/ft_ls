# include "ft_ls.h"
# include "vector.h"


void output(DIR* dir, ft_ls_s* ft_ls) {
    vector_s* entry_vector = make_vector(sizeof(struct dirent*), 25);
    if (!entry_vector) {
        return NULL;
    }
    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.' && !(ft_ls->selected_options && OPTION_ALL)) {
            continue;
        }
        ft_printf("%s ", entry->d_name);
    }
}
