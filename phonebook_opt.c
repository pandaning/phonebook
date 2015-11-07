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
static inline int fuzzySearch(char *str)
{
    return  strlen(str);
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
int min(int a, int b, int c)
{
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}
int Similarity(char *compare, char *compared)
{
    int L1 = strlen(compare), L2 = strlen(compared);
    char str1[L1+1], str2[L2+1];
    str1[0] = '*';
    str1[1] = 0;
    str2[0] = '*';
    str2[1] = 0;
    strcat(str1, compare);
    strcat(str2, compared);
    int dp[L1+1][L2+1];
    int i, j;

    for(i = 0; str1[i]; i++) {
        for(j = 0; str2[j]; j++) {
            if(i == 0) dp[i][j] = j;
            else if(j == 0) dp[i][j] = i;
            else {
                if(str1[i] == str2[j]) dp[i][j] = dp[i-1][j-1];
                else dp[i][j] =  min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]) + 1;
            }
        }
    }
    return dp[L1][L2];
}
void DoFuzzySearch(char *str)
{
    int cnt = 0;
    int id = HashFunc(str);
    for(HashList *tmp = head[id]; tmp; tmp = tmp->next) {
        if (Similarity(str, tmp->name) == 1) {
            printf("You input \"%s\"   Do you mean \"%s\"\n", str, tmp->name);
            cnt++;
        }
    }
    for(HashList *tmp = head[id-1]; tmp; tmp = tmp->next) {
        if (Similarity(str, tmp->name) == 1) {
            printf("You input \"%s\"   Do you mean \"%s\"\n", str, tmp->name);
            cnt++;
        }
    }
    for(HashList *tmp = head[id+1]; tmp; tmp = tmp->next) {
        if (Similarity(str, tmp->name) == 1) {
            printf("You input \"%s\"   Do you mean \"%s\"\n", str, tmp->name);
            cnt++;
        }
    }
    printf("There are %d similary words.\n", cnt);
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
/*Implementing abstraction with C*/
struct phonebook phonebook = {
    .init_Hash_Table = init_Hash_Table,
    .IsFound = IsFound,
    .push_Hash_Table = push_Hash_Table,
    .Release_Hash_Table = Release_Hash_Table,
    .DoFuzzySearch = DoFuzzySearch
};