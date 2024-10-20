# include "libft.h"

size_t ft_abs_value(long int nbr)
{
    return nbr < 0 ? -nbr : nbr;
}

int ft_max(int a, int b)
{
    return a > b ? a : b;
}

int ft_pow(int base, int exponent) {
    int multiplier = base;
    while (exponent-- > 1) {
        base *= multiplier;
    }
    return base;
}
