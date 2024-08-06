// The Algorithms
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_set.h"

extern hash_set_t *init_hash_set()
{
    hash_set_t *set = (hash_set_t *)malloc(sizeof(hash_set_t));
    set->keys = calloc(DEFAULT_HASH_SET_CAPACITY, sizeof(void **));
    set->values = calloc(DEFAULT_HASH_SET_CAPACITY, sizeof(void **));
    set->length = 0;
    set->capacity = DEFAULT_HASH_SET_CAPACITY;

    return set;
}

unsigned add(hash_set_t *set, void *value)
{
    return put(set, hash(value), value);
}

unsigned put(hash_set_t *set, long long hash, void *value)
{
    if (contains_hash(set, hash))
    {
        if (set->keys[retrieve_index_from_hash(hash, set->capacity)] == value)
        {
            return 0;
        }

        // collision
        resize(set);

        return put(set, hash, value);
    }

    set->keys[retrieve_index_from_hash(hash, set->capacity)] = value;
    set->values[set->length++] = value;

    return 1;
}

int contains(hash_set_t *set, void *value)
{
    return set->keys[retrieve_index_from_hash(hash(value), set->capacity)] ==
                   value
               ? 1
               : 0;
}

int contains_hash(hash_set_t *set, long long hash)
{
    return set->keys[retrieve_index_from_hash(hash, set->capacity)] ? 1 : 0;
}

void delete (hash_set_t *set, void *value)
{
    set->keys[retrieve_index_from_hash(hash(value), set->capacity)] = NULL;
}

// adler_32 hash
long long hash(void *value)
{
    char *str = value;

    int a = 1;
    int b = 0;
    const int MODADLER = 65521;

    for (int i = 0; str[i] != '\0'; i++)
    {
        a = (a + str[i]) % MODADLER;
        b = (b + a) % MODADLER;
    }

    return (b << 16) | a;
}

unsigned retrieve_index_from_hash(const long long hash, const unsigned capacity)
{
    return (capacity - 1) & (hash ^ (hash >> 12));
}

void resize(hash_set_t *set)
{
    void **keys_resized = calloc((set->capacity <<= 1), sizeof(void **));

    for (int i = 0; i < set->length; i++)
    {
        keys_resized[retrieve_index_from_hash(hash(set->values[i]),
                                              set->capacity)] = set->values[i];
    }

    free(set->keys);

    set->keys = keys_resized;

    void **new_values =
        (void **)realloc(set->values, set->capacity * sizeof(void **));
    set->values = new_values;
}
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Failed to open input file");
        return 1;
    }

    hash_set_t* set = init_hash_set();
    char operation[10];
    int key;
    while (fscanf(file, "%s %d", operation, &key) == 2) {
        if (strcmp(operation, "add") == 0) {
            add(set, &key);
            printf("Added %d\n", key);
        } else if (strcmp(operation, "remove") == 0) {
            delete(set, &key);
            printf("Removed %d\n", key);
        } else if (strcmp(operation, "contains") == 0) {
            int result = contains(set, &key);
            if (result == 1) {
                printf("Contains %d: %d\n", key, result);
            } else {
                printf("Does not contain %d\n", key);
            }
        } else {
            fprintf(stderr, "Unknown operation: %s\n", operation);
        }
    }
    
    fclose(file);
    
    // freeHashSet(set);
    
    return 0;
}