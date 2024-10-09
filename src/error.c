# include "ft_ls.h"

int make_error(const char* ft_ls_error, const char* error_string, int rval) {
    const char* errno_error = strerror(errno);
    if (!errno_error)
        return 1;
    ft_dprintf(STDERR_FILENO, "ls: %s '%s': %s\n", ft_ls_error, error_string, errno_error);
    return rval;
}

char* make_error_str(const char* ft_ls_error, const char* error_string) {
    const char* errno_error = strerror(errno);
    if (!errno_error)
        return NULL;
    char* rval;
    ft_sprintf(&rval, "ls: %s '%s': %s\n", ft_ls_error, error_string, errno_error);
    if (!rval) {
        free(rval);
        return NULL;
    }
    return rval;
}
