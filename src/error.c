# include "ft_ls.h"
# include "ft_printf.h"
# include "error.h"

int make_error(const char* ft_ls_error, const char* error_string, int rval) {
    const char* errno_error = strerror(errno);
    if (!errno_error)
        return 1;
    ft_printf("ft_ls: %s '%s': %s\n", ft_ls_error, error_string, errno_error);
    // free(errno_error);
    return rval;
}

char* make_error_str(const char* ft_ls_error, const char* error_string) {
    const char* errno_error = strerror(errno);
    if (!errno_error)
        return NULL;
    char* rval;
    ft_sprintf(&rval, "ft_ls: %s '%s': %s\n", ft_ls_error, error_string, errno_error);
    if (!rval) {
        free(rval);
        return NULL;
    }
    // free(errno_error);
    return rval;
}
