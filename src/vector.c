# include "vector.h"
# include "utils.h"
# include "ft_ls.h"
# include <dirent.h>

vector_s* vector_make(size_t capacity) {
    vector_s* vector = malloc(sizeof(vector_s));
    if (!vector) {
        return NULL;
    }

    vector->content = malloc(sizeof(dirent_stat_s*) * capacity);
    if (!vector->content) {
        ft_free(vector, 1);
        return NULL;
    }

    vector->capacity = capacity;
    vector->size = 0;

    return vector;
}

static int ft_realloc(vector_s* vector) {
    size_t old_capacity = vector->capacity;
    void* old_content = vector->content;
    void* new = malloc(sizeof(dirent_stat_s*) * old_capacity * 2);
    if (!new) {
        return 1;
    }
    ft_memcpy(new, old_content, (size_t)((sizeof(dirent_stat_s*) * vector->size) / sizeof(char)));
    vector->content = new;
    vector->capacity *= 2;

    return ft_free(old_content, 0);
}

vector_s* vector_push(vector_s* vector, struct dirent* elem, const char* parent_path) {
    if (vector->size == vector->capacity)
        if (ft_realloc(vector))
            return NULL;

    dirent_stat_s* el = malloc(sizeof(dirent_stat_s));
    if (!el)
        return NULL;
    const char* fullpath = ft_strjoin_path(parent_path, elem->d_name);
    if (!fullpath) {
        free(el);
        return NULL;
    }
    if (stat(fullpath, &el->stat)) {
        free((char*)fullpath);
        free(el);
        return NULL;
    }
    free((char*)fullpath);
    el->elem = elem;
    vector->content[vector->size++] = el;

    return vector;
}

vector_s* vector_pop(vector_s* vector) {
    if (vector->size > 0)
        vector->size--;
    return vector;
}

static void sort_compare(dirent_stat_s** a, dirent_stat_s** b) {
    dirent_stat_s* small;
    dirent_stat_s* big;
    const char* a_name = (*a)->elem->d_name;
    const char* b_name = (*b)->elem->d_name;
    int comp = ft_strcmp_dot(a_name, b_name) > 0;
    int reverse_sort = ft_ls.selected_options & OPTION_REVERSE_SORT;
    small = comp ? *a : *b;
    big = comp ? *b : *a;
    *a = reverse_sort ? small : big;
    *b = reverse_sort ? big : small;
}

void vector_sort(vector_s* vector) {
    for (size_t i = 0; i < vector->size; i++) {
        for (size_t j = i + 1; j < vector->size; j++) {
            sort_compare(&vector->content[i], &vector->content[j]);
        }
    }
}

void vector_free(vector_s* vector) {
    for (size_t i = 0; i < vector->size; i++)
        free(vector->content[i]);
    free(vector->content);
    free(vector);
}

// ino
visited_ino_s* init_visited(visited_ino_s* visited) {
    visited->ino = malloc(sizeof(ino_t) * 25);
    if (!visited->ino)
        return NULL;
    visited->capacity = 25;
    visited->size = 0;

    return visited;
}

int add_ino(visited_ino_s* visited, ino_t ino) { 
    if (visited->size == visited->capacity) {
        ino_t* new = malloc(sizeof(ino_t) * visited->capacity * 2);
        if (!new)
            return 1;
        ft_memcpy(new, visited->ino, (sizeof(ino_t) * visited->size));
        free(visited->ino);
        visited->ino = new;
        visited->capacity *= 2;
        return 0;
    } 
    visited->ino[visited->size++] = ino;
    return 0;
}

int has_ino(visited_ino_s* visited, ino_t ino) {
    for (size_t i = 0; i < visited->size; i++) {
        if (visited->ino[i] == ino)
            return 1;
    }
    return 0;
}

void show_ino(visited_ino_s* visited) {
    for (size_t i = 0; i < visited->size; i++) {
        ft_printf("%d,", visited->ino[i]);
    }
    write(1, "\n", 1);
}
