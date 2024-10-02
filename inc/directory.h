# pragma once
# include "vector.h"
# include "ft_ls.h"
# include "utils.h"

dir_s* get_directories(vector_s* entry_vector);
int dir_free(dir_s* dirs, int rval);