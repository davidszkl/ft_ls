# pragma once
#include "ft_ls.h"

int set_option_short(const char option, ft_ls_s* ft_ls);
int set_option_long(const char* option, ft_ls_s* ft_ls);
int handle_option(const char* option_str, ft_ls_s* ft_ls);
int handle_path(const char* path, DIR** dirs, int path_count, struct stat* statbuf);
int parse_arguments(int ac, char** av, ft_ls_s* ft_ls);