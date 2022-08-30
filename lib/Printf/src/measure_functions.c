#include "printf.h"

size_t measure_int(long long int nbr) {
    size_t rval = 1;

    while (nbr > 9) {
        rval++;
        nbr /= 10;
    }
    return rval;
}

size_t measure_unsigned(unsigned long long int nbr) {
    size_t rval = 1;

    while (nbr > 9) {
        rval++;
        nbr /= 10;
    }
    return rval;
}

size_t measure_hex(unsigned long long int nbr) {
    size_t rval = 1;

    while (nbr > 15) {
        rval++;
        nbr /= 16;
    }
    return rval;   
}