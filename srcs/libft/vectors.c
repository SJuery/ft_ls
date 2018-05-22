#include "libft.h"

void vector_init(t_vector *v)
{
    v->capacity = 4;
    v->total = 0;
    v->items = malloc(sizeof(void *) * v->capacity);
}

static void vector_resize(t_vector *v, int capacity)
{
    void **items = realloc(v->items, sizeof(void *) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

void vector_add(t_vector *v, void *item)
{
    if (v->capacity == v->total)
        vector_resize(v, v->capacity * 2);
    v->items[v->total++] = item;
}

void vector_set(t_vector *v, int index, void *item)
{
    if (index >= 0 && index < v->total)
        v->items[index] = item;
}

void *vector_get(t_vector *v, int index)
{
    if (index >= 0 && index < v->total)
        return v->items[index];
    return NULL;
}
