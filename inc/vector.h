# pragma once
#include "ft_ls.h"

typedef struct vector_s {
    void* content;
    size_t elem_size;
    size_t size;
    size_t capacity;
} vector_s;


vector_s* make_vector(size_t elem_size, size_t capacity);
int ft_realloc(vector_s* vector);
vector_s* push(vector_s* vector, void* elem);
vector_s* pop(vector_s* vector);
