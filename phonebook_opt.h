#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* original version */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);


typedef struct  HashList
{
	char name[20];
	struct HashList *next;
	

}HL;

HL *head[20000];
HL *ptr[20000];

void init();
int HashFunc(char *str,int method);//return pos;
int IsFound(char *str);
void pushHashTable(char *str,int id);
void FREE();
#endif
