# pragma once
# include "ft_ls.h"

int ft_free_output_long(output_long_s* output_long, int rval);
int ft_free_output_long_tab(output_long_s** output_long, int rval);
int is_dot_folder(char* name);
int is_symbolic_link(struct stat* stat);
int is_hidden_folder(char* name);
