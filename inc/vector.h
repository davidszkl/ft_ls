# pragma once
# include "ft_ls.h"

typedef struct vector_s {
    struct dirent** content;
    size_t size;
    size_t capacity;
} vector_s;


vector_s* vector_make(size_t capacity);
vector_s* vector_push(vector_s* vector, struct dirent* elem);
vector_s* vector_pop(vector_s* vector);
void vector_sort(vector_s* vector);
void vector_free(vector_s* vector);

// ino
visited_ino_s* init_visited(visited_ino_s* visited);
int add_ino(visited_ino_s* visited, ino_t ino);
int has_ino(visited_ino_s* visited, ino_t ino);
void show_ino(visited_ino_s* visited);
