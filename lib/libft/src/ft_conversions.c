# include "libft.h"

// string to number
int	ft_atoi(const char *str)
{
	unsigned int nbr = 0;
	int sign = 1;

	while (*str && ((*str >= 9 && *str <= 13) || *str == ' ')) {
		str++;
    }
	if (*str && (*str == '-' || *str == '+')) {
        if (*str == '-')
		    sign = -1;
        str++;
    }
	while (*str && *str >= '0' && *str <= '9') {
		nbr = nbr * 10 + *str - '0';
		str++;
	}
    if (!*str) return -1;
	if (sign == 1 && nbr > INT_MAX) return (-1);
	if (sign == -1 && nbr > (unsigned int)INT_MAX + 1) return (0);

	return nbr * sign;
}


// number to string

char* ft_itoa(int nbr) 
{
    int	tmp = nbr;
    size_t size = 1;

    while (tmp >= 10) {
        size++;
        tmp /= 10;
    }

    char* res = malloc((size + 1) * sizeof(char));
    if (!res)
        return NULL;

    int i = size - 1;
    while (nbr >= 10) {
        res[i--] = nbr % 10 + '0';
        nbr /= 10;
    }
    res[i] = nbr + '0';
    res[size] = '\0';

    return res;
}
