# include "vector.h"

vector_s* make_vector(size_t elem_size, size_t capacity) {
    vector_s* vector = malloc(sizeof(vector_s));
    if (!vector) {
        return NULL;
    }

    vector->content = malloc(elem_size * capacity);
    if (!vector->content) {
        return ft_free(vector);
    }

    vector->capacity = capacity;
    vector->elem_size = elem_size;
    vector->size = 0;

    return vector;
}

int ft_realloc(vector_s* vector) {
    size_t old_capacity = vector->capacity;
    void* old_content = vector->content;
    void* new = malloc(vector->elem_size * old_capacity * 2);
    if (!new) {
        return NULL;
    }
    ft_memcpy(new, old_content, (size_t)((vector->elem_size * vector->size) / sizeof(char)));
    vector->content = new;

    return fr_free(old_content);
}

vector_s* push(vector_s* vector, void* elem) {
    if (vector->size == vector->capacity) {
        if (!realloc(vector)) {
            return NULL;
        }
    }
    ft_memcpy(vector->content + vector->elem_size * vector->size, elem, vector->elem_size);
    vector->size++;

    return vector;
}

vector_s* pop(vector_s* vector) {
    vector->size > 0 ? vector->size-- : NULL;
    return vector;
}
