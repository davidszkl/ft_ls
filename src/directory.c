# include "ft_ls.h"
# include "vector.h"
# include "directory.h"
# include "error.h"

int is_dir(struct dirent* entry) {
    return opendir(entry->d_name) != NULL || errno != ENOTDIR;
}

int dir_count(vector_s* entry_vector) {
    int dircount = 0;
    for (size_t i = 0; i < entry_vector->size; i++) {
        dircount += is_dir(entry_vector->content[i]->elem);
    }
    return dircount;
}

static int init_dir_helpers(char** dir_path,  dir_s** dir_struct, dir_s* directories, vector_s* entry_vector, const char* path, size_t i, size_t dir_idx) {
    *dir_path = ft_strjoin_path(path, entry_vector->content[i]->elem->d_name);
    if (!dir_path)
        return 1;
    *dir_struct = &directories[dir_idx];
    (*dir_struct)->error = NULL;
    (*dir_struct)->dir = NULL;
    (*dir_struct)->name = NULL;
    return 0;
}

static int handle_dir_error(dir_s* directories, dir_s* dir_struct, const char* dir_path, size_t* dir_idx) {
    if (errno == EACCES || errno == ENOTDIR || errno == ENOENT) {
        if (errno == EACCES) {
            dir_struct->error = make_error_str(NO_OPEN, dir_path);
            *dir_idx += 1;
            directories->count = *dir_idx;
        }
        free((char*)dir_path);
        return 0;
    } else {
        free((char*)dir_path);
        return 1;
    }
}

static int fill_dir_struct(dir_s* dir_struct, char* dir_path, vector_s* entry_vector, DIR* directory, size_t i) {
    dir_struct->dir = directory;
    if (stat(dir_path, &dir_struct->stat))
        return 1;
    
    dir_struct->name = ft_strdup(entry_vector->content[i]->elem->d_name, -1);
    if (!dir_struct->name) 
        return 1;

    return 0;
}

dir_s* get_directories(vector_s* entry_vector, const char* path) {
    dir_s* directories = malloc(sizeof(dir_s) * (entry_vector->size + 1));
    if (!directories) 
        return NULL;
    ft_memset(directories, 0, sizeof(dir_s) * (entry_vector->size + 1));

    size_t dir_idx = 0;
    for (size_t i = 0; i < entry_vector->size; i++) {
        // init dir_struct and dir_path
        char* dir_path;
        dir_s* dir_struct;
        if (init_dir_helpers(&dir_path, &dir_struct, directories, entry_vector, path, i, dir_idx)) {
            free(directories);
            return NULL;
        }
        
        // open dir and handle error
        DIR* directory = opendir(dir_path);
        if (directory == NULL) {
            if (handle_dir_error(directories, dir_struct, dir_path, &dir_idx) == 0) continue;
            else continue;
        }

        // fill up dir structure
        if (fill_dir_struct(dir_struct, dir_path, entry_vector, directory, i)) {
            free((char*)dir_path);
            closedir(dir_struct->dir);
            dir_free(directories, 1);
            return NULL;
        }
        free((char*)dir_path);
        directories->count = ++dir_idx;
    }

    if (!(directories->count)) {
        directories->dir = NULL;
        directories->name = NULL;
        directories->error = NULL;
        ft_memset(&directories->stat, 0, sizeof(struct stat));
    }
    return directories;
}

int dir_free(dir_s* dirs, int rval) {
    for(size_t i = 0; i < dirs->count; i++) {
        closedir(dirs[i].dir);
        free(dirs[i].name);
        free(dirs[i].error);
    }
    free(dirs);
    return rval;
}