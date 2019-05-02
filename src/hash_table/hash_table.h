typedef struct ht_item {
    char* key;
    char* value;
    struct ht_item* next;
    struct ht_item* prev;
} ht_item;

typedef struct {
    ht_item* item;
    ht_item* next;
} ht_list_item;

typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;

ht_hash_table* ht_new();
void ht_free(ht_hash_table*);
void ht_insert(ht_hash_table* ht, char* key, char* value);
char* ht_search(ht_hash_table* ht, char* key);
