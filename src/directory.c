# include "directory.h"

static int init_dir_helpers(char** dir_path,  dir_s** dir_struct, dir_s* directories, vector_s* entry_vector, size_t i, size_t dir_idx) {
    *dir_path = ft_strjoin_path(ft_ls.parent_path, entry_vector->content[i].elem->d_name);
    if (!dir_path)
        return 1;
    *dir_struct = &directories[dir_idx];
    return 0;
}

static int handle_dir_error(dir_s* dir_struct, const char* dir_path, char* dir_name, size_t* dir_idx) {
    const int option_all = (&ft_ls)->selected_options & OPTION_ALL;
    if (errno == EACCES || errno == ENOTDIR || errno == ENOENT) {
        if (errno == EACCES) {
            dir_struct->name = ft_strdup(dir_name, -1);
            if (!dir_struct->name)
                return 1;
            if ((is_dot_folder(dir_struct->name) || is_hidden_folder(dir_struct->name)) && !option_all) {
                *dir_idx += 1;
                return 0;
            }
                
            dir_struct->error = make_error_str(NO_OPEN, dir_path);
            if (!dir_struct->error)
                return 1;
            *dir_idx += 1;
        }
        return 0;
    } else {
        return 1;
    }
}

static int fill_dir_struct(dir_s* dir_struct, char* dir_path, vector_s* entry_vector, DIR* directory, size_t i) {
    dir_struct->dir = directory;
    if (lstat(dir_path, &dir_struct->stat))
        return 1;
    
    dir_struct->name = ft_strdup(entry_vector->content[i].elem->d_name, -1);
    if (!dir_struct->name) 
        return 1;

    return 0;
}

dir_s* get_directories(vector_s* entry_vector) {
    dir_s* directories = ft_malloc_zero(sizeof(dir_s) * (entry_vector->size + 1));
    if (!directories) 
        return NULL;

    size_t dir_idx = 0;
    for (size_t i = 0; i < entry_vector->size; i++) {
        // init dir_struct and dir_path
        char* dir_path = NULL;
        dir_s* dir_struct = NULL;
        if (init_dir_helpers(&dir_path, &dir_struct, directories, entry_vector, i, dir_idx)) {
            free(directories);
            return NULL;
        }
        
        // open dir and handle error
        DIR* directory = opendir(dir_path);
        if (directory == NULL) {
            if (handle_dir_error(dir_struct, dir_path, entry_vector->content[i].elem->d_name, &dir_idx)) {
                free((char*)dir_path);
                closedir(dir_struct->dir);
                dir_free(directories, 1);
                return NULL;
            }
            free((char*)dir_path);
            continue;
        }

        // fill up dir structure, even if directory is NULL
        if (fill_dir_struct(dir_struct, dir_path, entry_vector, directory, i)) {
            free((char*)dir_path);
            closedir(dir_struct->dir);
            dir_free(directories, 1);
            return NULL;
        }

        dir_idx++;
        free((char*)dir_path);
    }

    directories->count = dir_idx;
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
