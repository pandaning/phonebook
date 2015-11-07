#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 15
#define HashFunc fuzzySearch //Choose which hash function to use.
#define HashTableSize 6997 //a prime number

/* Revised version */
typedef struct  HashList {
    char name[MAX_LAST_NAME_SIZE];
    struct HashList *next;
} HashList;

struct phonebook {
    void (*init_Hash_Table)(void);
    int (*IsFound)(char *str);
    void (*push_Hash_Table)(char *str);
    void (*Release_Hash_Table)(void);
    void (*DoFuzzySearch)(char *str);
};
HashList *head[HashTableSize];
HashList *ptr[HashTableSize];
struct phonebook phonebook;
#endif
