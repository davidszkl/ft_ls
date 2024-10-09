# pragma once
# include "ft_ls.h"
# include "error.h"
# include "utils.h"
# include "vector.h"

dir_s* get_directories(vector_s* entry_vector);
int dir_free(dir_s* dirs, int rval);
