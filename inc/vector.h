# pragma once
# include "ft_ls.h"
# include "error.h"

# define INITIAL_VECTOR_CAPACITY 15
# define INITIAL_INO_CAPACITY 15

typedef struct dirent_stat_t {
    struct dirent* elem;
    struct stat stat;
    char* error;
} dirent_stat_s;

typedef struct vector_t {
    dirent_stat_s* content;
    size_t size;
    size_t capacity;
} vector_s;

vector_s* vector_make(size_t capacity);
vector_s* vector_push(vector_s* vector, struct dirent* elem, const char* parent_path);
vector_s* vector_pop(vector_s* vector);
void vector_sort(vector_s* vector);
void vector_free(vector_s* vector);

// ino
visited_ino_s* init_visited(visited_ino_s* visited);
int add_ino(visited_ino_s* visited, ino_t ino);
int has_ino(visited_ino_s* visited, ino_t ino);
void show_ino(visited_ino_s* visited);
