# pragma once
#include "ft_ls.h"

int set_option_short(const char option);
int set_option_long(const char* option);
int handle_option(const char* option_str);
int handle_path(const char* path, dir_s* dirs, int path_count, struct stat* statbuf);
int parse_arguments(int ac, char** av);