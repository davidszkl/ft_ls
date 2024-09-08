# pragma once
# include "vector.h"
# include "ft_ls.h"

dir_s* get_directories(vector_s* entry_vector, const char* parent_path);
int dir_free(dir_s* dirs, int rval);