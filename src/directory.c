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

dir_s* get_directories(vector_s* entry_vector, const char* path) {
    dir_s* directories = malloc(sizeof(dir_s) * (entry_vector->size + 1));
    if (!directories) 
        return NULL;
    ft_memset(directories, 0, sizeof(dir_s*) * (entry_vector->size + 1));
    directories->count = 0;

    dir_s* dir_struct;
    size_t dir_idx = 0;
    for (size_t i = 0; i < entry_vector->size; i++) {
        const char* dir_path = ft_strjoin_path(path, entry_vector->content[i]->d_name);
        if (!dir_path) {
            free(directories);
            return NULL;
        }
        DIR* directory = opendir(dir_path);
        free((char*)dir_path);
        if (directory == NULL) {
            if (errno == ENOTDIR)
                continue;
            dir_free(directories, 1);
            return NULL;
        }

        dir_struct = &directories[dir_idx++];
        dir_struct->dir = directory;
        dir_struct->name = ft_strdup(entry_vector->content[i]->d_name, -1);
        if (!dir_struct->name) {
            closedir(dir_struct->dir);
            dir_free(directories, 1);
        }
        directories->count = dir_idx;
    }

    if (!(directories->count)) {
        directories->dir = NULL;
        directories->name = NULL;
    }
    return directories;
}

int dir_free(dir_s* dirs, int rval) {
    for(size_t i = 0; i < dirs->count; i++) {
        free(dirs[i].name);
        closedir(dirs[i].dir);
    }
    free(dirs);
    return rval;
}