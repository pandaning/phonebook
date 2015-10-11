#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "phonebook_opt.h"

void init_Hash_Table()
{
    for(int i=0; i<HashTableSize; i++) {
        head[i]=malloc(sizeof(HashList));
        head[i]->next=NULL;
        ptr[i]=head[i];
    }
}
static inline int LoseLose(char *str)
{
    unsigned int id=0;
    for(int i=0; str[i]; i++) {
        id+=str[i];
    }
    return id%HashTableSize;
}
static inline int ShiftMethod(char *str)
{
    unsigned int id=0;
    for(int i=0; str[i]; i++) {
        id+=str[i]<<i;
    }
    return id%HashTableSize;
}
static inline int djb2(char*str)
{
    unsigned id=5381;
    for(int i=0; str[i]; i++) {
        id=((id<<5)+id)+str[i];
    }
    return id%HashTableSize;
}
static inline int sdbm(char *str)
{
    unsigned int id=0;
    for(int i=0; str[i]; i++) {
        id=((id<<6)+(id<<16)) - id + str[i];
    }
    return id%HashTableSize;
}
int IsFound(char str[])
{
    int id=HashFunc(str);//check which table the string is in
    for(HashList* tmp=head[id] ; tmp!=NULL ; tmp=tmp->next) {
        if(strcmp(tmp->name , str)==0) { //if(tmp->name==str)
            return 1;
        }
    }
    return 0;
}
void push_Hash_Table(char *str)
{
    int id=HashFunc(str);
    ptr[id]->next=malloc(sizeof(HashList));
    ptr[id]=ptr[id]->next;
    strcpy(ptr[id]->name,str);     //ptr[id]->name=str;
    ptr[id]->next=NULL;
}
/*To release each node in the Linked-List malloced*/
void Release_Hash_Table()
{
    for(int i=0; i<HashTableSize; i++) {
        HashList *tmp=head[i];
        HashList *f=tmp;
        if(tmp->next!=NULL)tmp=tmp->next;
        for(; tmp->next!=NULL; tmp=tmp->next) {
            free(f);
            f=tmp;
        }
    }
}