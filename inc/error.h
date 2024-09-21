# define NO_ACCESS "cannot access"
# define NO_OPEN "cannot open directory"

int make_error(const char* ft_ls_error, const char* error_string, int rval);
char* make_error_str(const char* ft_ls_error, const char* error_string);
