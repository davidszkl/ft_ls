#include <limits.h>

int	ft_atoi(const char *str)
{
	unsigned int nbr = 0;
	int sign = 1;

	while ((*str >= 9 && *str <= 13) || *str == ' ') {
		str++;
    }
	if (*str == '-' || *str == '+') {
        if (*str == '-')
		    sign = -1;
        str++;
    }
	while (*str >= '0' && *str <= '9') {
		nbr = nbr * 10 + *str - '0';
		str++;
	}
	if (sign == 1 && nbr > INT_MAX) return (-1);
	if (sign == -1 && nbr > (unsigned int)INT_MAX + 1) return (0);

	return nbr * sign;
}

int ft_strlen(const char* str) {
    int len = 0;
    while (*str++) {
        len++;
    }
    return len;
}

int ft_isdigit(const char c) {
    return c >= '0' && c <= '9';
}
