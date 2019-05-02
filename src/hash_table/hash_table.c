#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "hash_table.h"

static ht_item_t* ht_new_item(const char* key, const char* value) {
    ht_item_t* item = malloc(sizeof(ht_item_t));
    item->key = strdup(key);
    item->value = strdup(value);
    return item;
}

static void ht_free_item(ht_item_t* item) {
    free(item->value);
    free(item->key);
    free(item);
}

// TODO: Add item linked list length limiter.
// In case when item linked list equals to limiter
// hash table items array should growth up (aka rehash all items).
ht_hash_table_t* ht_new() {
    ht_hash_table_t* ht = malloc(sizeof(ht_hash_table_t));
    ht->size = 100;
    ht->count = 0;
    ht->items = calloc(ht->size, sizeof(ht_item_t*));
    return ht;
}

void ht_free(ht_hash_table_t* ht) {
    for(int i = 0; i < ht->size; i++) {
        ht_item_t* item = ht->items[i];
        if (item != NULL) {
            ht_free_item(ht->items[i]);
        }
    }
    free(ht->items);
    free(ht);
}

// TODO: Remove "attemt" argument, or just
// think about how to refactor hash function.
static int ht_hash(const char* s, const int a, const int buckets) {
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash += (long) pow(a, len_s - (i + 1)) * s[i];
        hash = hash % buckets;
    }

    return (int) hash;
}

static int ht_index(const char* s, const int buckets) {
    return ht_hash(s, 1, buckets);
}

static ht_item_t* ht_search_item(ht_hash_table_t* ht, char* key) {
    int idx = ht_index(key, ht->size);
    ht_item_t* item = ht->items[idx];

    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item;
        }
        item = item->next;
    }

    return item;
}

void ht_insert(ht_hash_table_t* ht, char* key, char* value) {
    ht_item_t* item = ht_new_item(key, value);
    int idx = ht_index(key, ht->size);
    ht_item_t* curr = ht_search_item(ht, key);

    ht->count++;

    if (curr == NULL) {
        ht->items[idx] = item;
        return;
    }

    while (curr->next != NULL) {
        if (strcmp(curr->next->key, key) == 0) {
            break;
        }
        curr = curr->next;
    }

    ht_item_t* next = curr->next;
    item->next = next->next;
    item->prev = curr;
    curr->next = item;

    ht_free_item(next);
}

void ht_delete(ht_hash_table_t* ht, char* key) {
    ht_item_t* item = ht_search_item(ht, key);
    if (item == NULL) {
        return;
    }

    if (item->prev != NULL) {
        item->prev->next = item->next;
    }

    ht_free_item(item);
    ht->count--;
}

char* ht_search(ht_hash_table_t* ht, char* key) {
    ht_item_t* item = ht_search_item(ht, key);
    if (item != NULL) {
        return item->value;
    }
    return NULL;
}
