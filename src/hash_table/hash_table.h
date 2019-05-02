typedef struct ht_item {
    char* key;
    char* value;
    struct ht_item* next;
    struct ht_item* prev;
} ht_item_t;

typedef struct {
    int size;
    int count;
    ht_item_t** items;
} ht_hash_table_t;

ht_hash_table_t* ht_new();
void ht_free(ht_hash_table_t*);
void ht_insert(ht_hash_table_t* ht, char* key, char* value);
char* ht_search(ht_hash_table_t* ht, char* key);
