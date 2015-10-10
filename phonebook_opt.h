#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 15

#define method  2      //Choose which hash function to use.
#define HashTableSize 69997 //a prime number

/* Revised version */
typedef struct  HashList {
    char name[MAX_LAST_NAME_SIZE];
    struct HashList *next;
} HashList;

HashList *head[HashTableSize];
HashList *ptr[HashTableSize];

void init_Hash_Table();
int HashFunc(char *str);//return pos;
int IsFound(char *str);
void push_Hash_Table(char *str,int id);
void Release_Hash_Table();
#endif
