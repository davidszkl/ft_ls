# include "ft_ls.h"
# include "vector.h"
# include "directory.h"

int is_dir(struct dirent* entry) {
    return opendir(entry->d_name) != NULL || errno != ENOTDIR;
}

int dir_count(vector_s* entry_vector) {
    int dircount = 0;
    for (size_t i = 0; i < entry_vector->size; i++) {
        dircount += is_dir(entry_vector->content[i]);
    }
    return dircount;
}

dir_s* get_directories(vector_s* entry_vector) {
    dir_s* directories = malloc(sizeof(dir_s*) * (entry_vector->size + 1));
    if (!directories) 
        return NULL;
    ft_memset(directories, 0, sizeof(dir_s*) * (entry_vector->size + 1));

    dir_s dir_struct;
    for (size_t i = 0; i < entry_vector->size; i++) {
        dir_struct = directories[i];

        DIR* directory = opendir(entry_vector->content[i]->d_name);
        if (directory == NULL) {
            if (errno == ENOTDIR)
                continue;
            return NULL;
        }

        dir_struct.dir = directory;
        dir_struct.name = entry_vector->content[i]->d_name;
    }

    return directories;
}