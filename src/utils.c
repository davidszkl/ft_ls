# include "utils.h"

int ft_free_output_long(output_long_s* output_long, int rval) {
    if (output_long->free_fname)
        free(output_long->fname);
    free(output_long->error);
    return rval;
}

int ft_free_output_long_tab(output_long_s* output_long, int rval) {
    size_t count = output_long[0].count ? output_long[0].count : 1;
    for (size_t i = 0; i < count; i++) {
        ft_free_output_long(&output_long[i], 0);
    }
    free(output_long);
    return rval;
}

int is_dot_folder(char* name) {
    return ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0;
}

int is_symbolic_link(struct stat* stat) {
    return S_ISLNK(stat->st_mode);
}

int is_hidden_folder(char* name) {
    return name[0] && name[0] == '.';
}
