#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    /* TODO: implement */
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    return NULL;
}

void init()
{
    for(int i=0; i<HashTableSize; i++) {
        head[i]=malloc(sizeof(HashList));
        head[i]->next=NULL;
        ptr[i]=head[i];
    }
}
int HashFunc(char *str)//return pos
{
    unsigned long long int pos=0;
    int strLength =  strlen(str);
    int chooseMethod = method;
    switch(chooseMethod) {
    case 1:
        for(int i=0; i<strLength; i++) {
            pos+=str[i];
        }
        break;
    case 2:
        for(int i=0; i<strLength; i++) {
            pos+=str[i]<<i;
        }
        break;
    case 3:
        pos=5381;
        for(int i=0; str[i]; i++) {
            pos=((pos<<5)+pos)+str[i];
        }
        break;
    case 4:
        for(int i=0; str[i]; i++) {
            pos=((pos<<6)+(pos<<16)) - pos + str[i];
        }
        break;
    default:
        break;
    }
    return pos%HashTableSize;
}
int IsFound(char str[])
{
    int yes=1;
    int no=0;
    int id=HashFunc(str);
    for(HashList* tmp=head[id] ; tmp!=NULL ; tmp=tmp->next) {
        if(strcmp(tmp->name , str)==0) { //if(tmp->name==str)
            return yes;
        }
    }
    return no;
}
void pushHashTable(char *str,int id)
{
    ptr[id]->next=malloc(sizeof(HashList));
    ptr[id]=ptr[id]->next;
    strcpy(ptr[id]->name,str);     //ptr[id]->name=str;
    ptr[id]->next=NULL;
}

void FREE_HashTable()
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